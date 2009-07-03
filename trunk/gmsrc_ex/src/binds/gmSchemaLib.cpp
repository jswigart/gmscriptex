#include "gmConfig.h"
#include "gmSchemaLib.h"
#include "gmThread.h"
#include "gmMachine.h"
#include "gmHelpers.h"

gmType GM_SCHEMA = GM_NULL;
gmType GM_SCHEMA_ELEMENT = GM_NULL;

//////////////////////////////////////////////////////////////////////////

class SchemaErrors
{
public:
	void VA(const char* _msg, ...)
	{
		char buffer[8192] = {0};
		va_list list;
		va_start(list, _msg);
#ifdef WIN32
		_vsnprintf(buffer, 8192, _msg, list);	
#else
		vsnprintf(buffer, 8192, _msg, list);
#endif
		va_end(list);
		m_Errors->Set(m_Machine,gmVariable(m_NumErrors++),buffer);
	}
	int NumErrors() const { return m_NumErrors; }
	gmTableObject *GetTable() const { return m_Errors; }
	void DumpToLog(gmLog &log)
	{
		gmTableIterator tIt;
		gmTableNode *pNode = m_Errors->GetFirst(tIt);
		while(pNode)
		{
			const char *Msg = pNode->m_value.GetCStringSafe(0);
			log.LogEntry(Msg);
			pNode = m_Errors->GetNext(tIt);
		}
	}
	void PrintErrors(gmMachine *a_machine)
	{
		gmTableIterator tIt;
		gmTableNode *pNode = m_Errors->GetFirst(tIt);
		while(pNode)
		{
			const char *Msg = pNode->m_value.GetCStringSafe(0);
			gmMachine::s_printCallback(a_machine,Msg);
			pNode = m_Errors->GetNext(tIt);
		}
	}
	SchemaErrors(gmMachine *a_machine) 
		: m_Machine(a_machine)
		, m_Errors(a_machine->AllocTableObject())
		, m_NumErrors(0)
	{
	}
private:
	gmMachine		*m_Machine;
	gmTableObject	*m_Errors;
	int				m_NumErrors;
};

//////////////////////////////////////////////////////////////////////////
static bool CheckIfVarsAreEqual(const gmVariable &a, const gmVariable &b)
{
	if(a.m_type == b.m_type)
	{
		if(a.IsReference())
			return a.m_value.m_ref == b.m_value.m_ref;
		else
		{
			switch(a.m_type)
			{
			case GM_INT:
				return a.m_value.m_int == b.m_value.m_int;
				break;
			case GM_FLOAT:
				return a.m_value.m_float == b.m_value.m_float;
				break;
			case GM_VEC3:
				return 
					a.m_value.m_vec3.x == b.m_value.m_vec3.x && 
					a.m_value.m_vec3.y == b.m_value.m_vec3.y && 
					a.m_value.m_vec3.z == b.m_value.m_vec3.z;
				break;
			case GM_ENTITY:
				return a.m_value.m_enthndl == b.m_value.m_enthndl;
				break;
			default:
				GM_ASSERT(0);
				break;
			}
		}
	}
	return false;
}

static bool VerifyValue(gmMachine *a_machine, gmTableObject *a_SchemaEl, gmVariable &a_var, SchemaErrors &a_errs, const char *a_field)
{
	//////////////////////////////////////////////////////////////////////////
	if(gmTableObject *EnumTbl = a_SchemaEl->Get(a_machine,"enum").GetTableObjectSafe())
	{
		bool Good = false;
		gmTableIterator enumIt;
		gmTableNode *pEnumNode = EnumTbl->GetFirst(enumIt);
		while(pEnumNode && !Good)
		{
			if(CheckIfVarsAreEqual(pEnumNode->m_value, a_var))
			{
				Good = true;
				break;
			}
			pEnumNode = EnumTbl->GetNext(enumIt);
		}
		if(!Good)
		{
			enum { BufferSize=256 };
			char buffervar[BufferSize] = { " " };
			const char *VarStr = a_var.AsString(a_machine,buffervar,BufferSize);
			a_errs.VA("'%s': no match for '%s'",a_field,VarStr);
		}
		return Good;
	}
	//////////////////////////////////////////////////////////////////////////
	if(const char *tableof = a_SchemaEl->Get(a_machine,"table").GetCStringSafe(0))
	{
		if(a_var.GetTableObjectSafe()!=NULL)
			return true;
		else
		{
			a_errs.VA("'%s': expected table, got %s",
				a_field,
				a_machine->GetTypeName(a_var.m_type));
		}
		return a_var.GetTableObjectSafe()!=NULL;
	}
	//////////////////////////////////////////////////////////////////////////
	const char *tableType = a_SchemaEl->Get(a_machine,"tableof").GetCStringSafe(0);
	gmTableObject *tableCheck = a_SchemaEl->Get(a_machine,"validatewith").GetTableObjectSafe();
	if(tableType || tableCheck)
	{
		gmTableObject *valTable = a_var.GetTableObjectSafe();
		if(valTable)
		{
			bool Good = true;

			gmTableIterator tIt;
			gmTableNode *tableNode = valTable->GetFirst(tIt);
			while(tableNode)
			{
				if(tableType)
				{
					// verify type
					if(!_gmstricmp(tableType,a_machine->GetTypeName(tableNode->m_value.m_type)))
					{
						// good!
					}
					else
					{
						Good = false;

						enum { BufferSize=256 };
						char buffervar[BufferSize] = { " " };
						const char *KeyStr = tableNode->m_key.AsString(a_machine,buffervar,BufferSize);

						a_errs.VA("'%s': expected table of %s, got %s at key %s",
							a_field,
							tableType,
							a_machine->GetTypeName(tableNode->m_value.m_type),
							KeyStr);
					}
				}
				else if(tableCheck)
				{
					Good = true;
					
					bool Validated = false;

					gmTableIterator valIt;
					gmTableNode *validateNode = tableCheck->GetFirst(valIt);
					while(validateNode)
					{
						// compare key/vs values differently in certain cases?
						if(CheckIfVarsAreEqual(validateNode->m_value,tableNode->m_key))
						{
							Validated = true;
							break;
						}
						validateNode = tableCheck->GetNext(valIt);
					}

					if(!Validated)
					{
						Good = false;

						enum { BufferSize=256 };
						char buffervar[BufferSize] = { " " };
						const char *KeyStr = tableNode->m_key.AsString(a_machine,buffervar,BufferSize);

						a_errs.VA("'%s': expected table with validation, got %s at key %s",
							a_field,
							a_machine->GetTypeName(tableNode->m_value.m_type),
							KeyStr);
					}
				}
				
				tableNode = valTable->GetNext(tIt);
			}
			return Good;
		}
		else
		{
			if(tableType)
			{
				a_errs.VA("'%s': expected table of %s, got %s",
					a_field,
					tableType,
					a_machine->GetTypeName(a_var.m_type));
			}
			else
			{
				a_errs.VA("'%s': expected table, got %s",
					a_field,
					a_machine->GetTypeName(a_var.m_type));
			}
		}
		return false;
	}	
	//////////////////////////////////////////////////////////////////////////
	if(!a_SchemaEl->Get(a_machine,"numrange").IsNull())
	{
		if(!a_var.IsNumber())
		{
			a_errs.VA("'%s': expected number, got %s",a_field,a_machine->GetTypeName(a_var.m_type));
			return false;
		}
		const float Value = a_var.GetFloatSafe();

		gmVariable varMin = a_SchemaEl->Get(a_machine,"range_min");
		gmVariable varMax = a_SchemaEl->Get(a_machine,"range_max");

		float RangeMin = -FLT_MAX, RangeMax = FLT_MAX;
		const bool GotMin = varMin.GetFloatSafe(RangeMin);
		const bool GotMax = varMax.GetFloatSafe(RangeMax);

		enum { BufferSize=256 };
		char buffervar[BufferSize] = { " " };
		char buffermin[BufferSize] = { " " };
		char buffermax[BufferSize] = { " " };
		const char *VarStr = a_var.AsString(a_machine,buffervar,BufferSize);
		const char *MinStr = varMin.AsString(a_machine,buffermin,BufferSize);
		const char *MaxStr = varMax.AsString(a_machine,buffermax,BufferSize);

		if(GotMin && Value < RangeMin)
		{
			a_errs.VA("%s%s%snumber out of range %s, expected (%s..%s)",
				a_field?"'":"",
				a_field?a_field:"",
				a_field?"': ":"",
				VarStr,
				MinStr?MinStr:" ",
				MaxStr?MaxStr:" ");
			return false;
		}
		if(GotMax && Value > RangeMax)
		{
			a_errs.VA("%s%s%snumber out of range %s, expected (%s..%s)",
				a_field?"'":"",
				a_field?a_field:"",
				a_field?"': ":"",
				VarStr,
				MinStr?MinStr:" ",
				MaxStr?MaxStr:" ");
			return false;
		}
		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	if(!a_SchemaEl->Get(a_machine,"intrange").IsNull())
	{
		a_SchemaEl->Get(a_machine,"range_min");
		a_SchemaEl->Get(a_machine,"range_max");

	}
	//////////////////////////////////////////////////////////////////////////
	if(!a_SchemaEl->Get(a_machine,"floatrange").IsNull())
	{
		a_SchemaEl->Get(a_machine,"range_min");
		a_SchemaEl->Get(a_machine,"range_max");

	}
	return false;
}

//////////////////////////////////////////////////////////////////////////

static int GM_CDECL gmfSchemaCheck(gmThread * a_thread)
{
	GM_TABLE_PARAM(errortable,1,0);

	SchemaErrors err(a_thread->GetMachine());

	gmTableObject *checktable = a_thread->Param(0).GetTableObjectSafe();
	gmUserObject *checkUser = a_thread->Param(0).GetUserObjectSafe();

	if(checktable || checkUser)
	{
		gmMachine *pM = a_thread->GetMachine();
		gmTableObject *SchemaTable = static_cast<gmTableObject*>(a_thread->ThisUserCheckType(GM_SCHEMA));

		gmTableIterator tIt;
		gmTableNode *pNode = SchemaTable->GetFirst(tIt);
		while(pNode)
		{
			gmTableObject *SchemaDef = static_cast<gmTableObject*>(pNode->m_value.GetUserSafe(GM_SCHEMA_ELEMENT));
			gmVariable SchemaDefault = SchemaDef->Get(pM,"default");
			GM_ASSERT(SchemaDef);

			//////////////////////////////////////////////////////////////////////////
			// Tables
			if(checktable)
			{
				gmVariable checkVar = checktable->Get(pNode->m_key);
				if(checkVar.IsNull())
				{
					const char *FieldName = pNode->m_key.GetCStringSafe(0);
					err.VA("'%s' expected.",FieldName?FieldName:"<ERROR>");
				}
				else
				{
					const char *FieldName = pNode->m_key.GetCStringSafe("<?>");
					VerifyValue(pM,SchemaDef,checkVar,err,FieldName);
				}
			}
			else if(checkUser)
			{
				gmOperatorFunction getdot = a_thread->GetMachine()->GetTypeNativeOperator(checkUser->GetType(),O_GETDOT);
				gmOperatorFunction setdot = a_thread->GetMachine()->GetTypeNativeOperator(checkUser->GetType(),O_SETDOT);

				if(getdot && setdot)
				{
					bool SetDefaultValue = false;

					// A bit hacky, but the only reliable way to support schema validation on user objects.
					gmVariable vars[3] = { gmVariable(checkUser), pNode->m_key, gmVariable::s_null };
					getdot(a_thread,vars);
					gmVariable checkVar = vars[0];
					if(checkVar.IsNull())
					{
						SetDefaultValue = true;
						if(SchemaDefault.IsNull())
						{
							const char *FieldName = pNode->m_key.GetCStringSafe(0);
							err.VA("'%s' expected.",FieldName?FieldName:"<ERROR>");
						}
					}
					else
					{
						const char *FieldName = pNode->m_key.GetCStringSafe("<?>");
						if(!VerifyValue(pM,SchemaDef,checkVar,err,FieldName))
						{
							SetDefaultValue = true;
						}
					}

					// initialize to the default value.
					if(SetDefaultValue && !SchemaDefault.IsNull())
					{
						gmVariable newKey = pNode->m_key;
						gmVariable newValue = SchemaDefault;

						// special case, tables should be duplicated, not their reference shared.
						gmTableObject *DefaultTable = SchemaDefault.GetTableObjectSafe();
						if(DefaultTable)
						{
							gmTableObject *NewTable = pM->AllocTableObject();
							DefaultTable->CopyTo(pM,NewTable);
							newValue = gmVariable(NewTable);
						}

						vars[0] = gmVariable(checkUser);
						vars[1] = newValue;
						vars[2] = newKey;
						setdot(a_thread,vars);
					}
				}
				else
				{
					const char *FieldName = pNode->m_key.GetCStringSafe(0);
					err.VA("'%s' expected, unable to validate, must have getdot and setdot operators.",
						FieldName?FieldName:"<ERROR>");
				}
			}
			pNode = SchemaTable->GetNext(tIt);
		}

		if(errortable)
		{
			gmTableObject *errTbl = err.GetTable();
			gmTableIterator tIt;
			gmTableNode *pNode = errTbl->GetFirst(tIt);
			while(pNode)
			{
				errortable->Set(a_thread->GetMachine(),pNode->m_key,pNode->m_value);
				pNode = errTbl->GetNext(tIt);
			}
		}
		a_thread->PushInt(err.NumErrors()==0);
	}
	return GM_OK;
}

//////////////////////////////////////////////////////////////////////////
#define CREATE_ELEMENT() \
	gmTableObject *tbl = a_thread->GetMachine()->AllocTableObject(); \
	gmUserObject *obj = a_thread->GetMachine()->AllocUserObject(tbl,GM_SCHEMA_ELEMENT);

static int gmfSchemaEnum(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	CREATE_ELEMENT();

	gmTableObject *enums = a_thread->GetMachine()->AllocTableObject();
	for(int i = 0; i < a_thread->GetNumParams(); ++i)
		enums->Set(a_thread->GetMachine(),i,a_thread->Param(i));
	tbl->Set(a_thread->GetMachine(),"enum",gmVariable(enums));
	a_thread->PushUser(obj);
	return GM_OK;
}

static int gmfSchemaFloatRange(gmThread *a_thread)
{
	GM_FLOAT_PARAM(n1,0,-FLT_MAX);
	GM_FLOAT_PARAM(n2,1, FLT_MAX);
	CREATE_ELEMENT();

	gmTableObject *enums = a_thread->GetMachine()->AllocTableObject();
	for(int i = 0; i < a_thread->GetNumParams(); ++i)
		enums->Set(a_thread->GetMachine(),i,a_thread->Param(i));
	tbl->Set(a_thread->GetMachine(),"floatrange",gmVariable(1));
	tbl->Set(a_thread->GetMachine(),"range_min",gmVariable(n1));
	tbl->Set(a_thread->GetMachine(),"range_max",gmVariable(n2));
	a_thread->PushUser(obj);
	return GM_OK;
}

static int gmfSchemaIntRange(gmThread *a_thread)
{
	GM_INT_PARAM(n1,0,-INT_MAX);
	GM_INT_PARAM(n2,1, INT_MAX);
	CREATE_ELEMENT();

	gmTableObject *enums = a_thread->GetMachine()->AllocTableObject();
	for(int i = 0; i < a_thread->GetNumParams(); ++i)
		enums->Set(a_thread->GetMachine(),i,a_thread->Param(i));
	tbl->Set(a_thread->GetMachine(),"intrange",gmVariable(1));
	tbl->Set(a_thread->GetMachine(),"range_min",gmVariable(n1));
	tbl->Set(a_thread->GetMachine(),"range_max",gmVariable(n2));
	a_thread->PushUser(obj);
	return GM_OK;
}

static int gmfSchemaNumRange(gmThread *a_thread)
{
	GM_FLOAT_OR_INT_PARAM(n1,0,-FLT_MAX);
	GM_FLOAT_OR_INT_PARAM(n2,1, FLT_MAX);
	CREATE_ELEMENT();

	gmTableObject *enums = a_thread->GetMachine()->AllocTableObject();
	for(int i = 0; i < a_thread->GetNumParams(); ++i)
		enums->Set(a_thread->GetMachine(),i,a_thread->Param(i));
	tbl->Set(a_thread->GetMachine(),"numrange",gmVariable(1));
	tbl->Set(a_thread->GetMachine(),"range_min",gmVariable(n1));
	tbl->Set(a_thread->GetMachine(),"range_max",gmVariable(n2));
	a_thread->PushUser(obj);
	return GM_OK;
}

static int gmfSchemaTable(gmThread *a_thread)
{
	CREATE_ELEMENT();

	tbl->Set(a_thread->GetMachine(),"table",gmVariable(1));
	a_thread->PushUser(obj);
	return GM_OK;
}

static int gmfSchemaTableOf(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	CREATE_ELEMENT();

	if(a_thread->ParamType(0)==GM_STRING)
		tbl->Set(a_thread->GetMachine(),"tableof",a_thread->Param(0));
	else if(a_thread->ParamType(0)==GM_TABLE)
		tbl->Set(a_thread->GetMachine(),"validatewith",a_thread->Param(0));
	else
	{
		GM_EXCEPTION_MSG("expected string or table for validation");
		return GM_EXCEPTION;
	}
	a_thread->PushUser(obj);
	return GM_OK;
}

//////////////////////////////////////////////////////////////////////////

static int gmfSchemaElementDefault(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	gmTableObject *tbl = static_cast<gmTableObject*>(a_thread->ThisUserCheckType(GM_SCHEMA_ELEMENT));
	GM_ASSERT(tbl);

	SchemaErrors errs(a_thread->GetMachine());
	if(VerifyValue(a_thread->GetMachine(),tbl,a_thread->Param(0),errs,0))
	{
		tbl->Set(a_thread->GetMachine(),"default",a_thread->Param(0));
		a_thread->PushUser(a_thread->ThisUserObject());
	}
	else
	{
		errs.DumpToLog(a_thread->GetMachine()->GetLog());
		return GM_EXCEPTION;
	}	
	return GM_OK;
}

static int gmfSchemaElementCheck(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	gmTableObject *tbl = static_cast<gmTableObject*>(a_thread->ThisUserCheckType(GM_SCHEMA_ELEMENT));
	GM_ASSERT(tbl);

	SchemaErrors errs(a_thread->GetMachine());
	const bool Verified = VerifyValue(a_thread->GetMachine(),tbl,a_thread->Param(0),errs,0);

	a_thread->PushInt(Verified?1:0);
	return GM_OK;
}

static int gmfSchemaElementCheckPrintErrors(gmThread *a_thread)
{
	GM_CHECK_NUM_PARAMS(1);
	gmTableObject *tbl = static_cast<gmTableObject*>(a_thread->ThisUserCheckType(GM_SCHEMA_ELEMENT));
	GM_ASSERT(tbl);

	SchemaErrors errs(a_thread->GetMachine());
	const bool Verified = VerifyValue(a_thread->GetMachine(),tbl,a_thread->Param(0),errs,0);

	errs.PrintErrors(a_thread->GetMachine());

	a_thread->PushInt(Verified?1:0);
	return GM_OK;
}

//////////////////////////////////////////////////////////////////////////

int gmfCreateSchema(gmThread *a_thread)
{
	gmTableObject *SchemaTbl = a_thread->GetMachine()->AllocTableObject();
	a_thread->PushNewUser(SchemaTbl,GM_SCHEMA);
	return GM_OK;
}

//////////////////////////////////////////////////////////////////////////
// Trace Functions

static bool gmfTraceSchema(gmMachine *a_machine, gmUserObject*a_object, gmGarbageCollector*a_gc, const int a_workLeftToGo, int& a_workDone)
{
	GM_ASSERT(a_object->GetType()==GM_SCHEMA);
	gmTableObject *Tbl = static_cast<gmTableObject*>(a_object->m_user);
	if(Tbl)
	{
		a_gc->GetNextObject(Tbl);
		a_workDone++;
	}
	return true;
}

static bool gmfTraceSchemaElement(gmMachine *a_machine, gmUserObject*a_object, gmGarbageCollector*a_gc, const int a_workLeftToGo, int& a_workDone)
{
	GM_ASSERT(a_object->GetType()==GM_SCHEMA_ELEMENT);
	gmTableObject *Tbl = static_cast<gmTableObject*>(a_object->m_user);
	if(Tbl)
	{
		a_gc->GetNextObject(Tbl);
		a_workDone++;
	}	
	return true;
}

//////////////////////////////////////////////////////////////////////////

static void GM_CDECL gmSchemaGetDot(gmThread * a_thread, gmVariable * a_operands)
{
	gmTableObject *Tbl = static_cast<gmTableObject*>(a_operands[0].GetUserSafe(GM_SCHEMA));
	GM_ASSERT(Tbl);
	if(Tbl)
	{
		a_operands[0] = Tbl->Get(a_operands[1]);
		return;
	}
	a_operands[0].Nullify();
}

static void GM_CDECL gmSchemaSetDot(gmThread * a_thread, gmVariable * a_operands)
{
	gmTableObject *Tbl = static_cast<gmTableObject*>(a_operands[0].GetUserSafe(GM_SCHEMA));
	GM_ASSERT(Tbl);
	if(Tbl)
	{
		Tbl->Set(a_thread->GetMachine(),a_operands[2],a_operands[1]);
		return;
	}
	a_operands[0].Nullify();
}

//////////////////////////////////////////////////////////////////////////

static gmFunctionEntry s_schemaLib[] = 
{ 
	{"Schema", gmfCreateSchema},
};

//////////////////////////////////////////////////////////////////////////

static gmFunctionEntry s_schemaTypeLib[] = 
{ 
	{"Check", gmfSchemaCheck},
};

//////////////////////////////////////////////////////////////////////////

static gmFunctionEntry s_schemaElementTypeLib[] = 
{ 
	{"Default", gmfSchemaElementDefault},
	{"Check", gmfSchemaElementCheck},
	{"CheckPrintErrors", gmfSchemaElementCheckPrintErrors},
};

//////////////////////////////////////////////////////////////////////////

static gmFunctionEntry s_createElementLib[] = 
{ 
	{"Table", gmfSchemaTable},
	{"TableOf", gmfSchemaTableOf},
	{"Enum", gmfSchemaEnum},
	{"FloatRange", gmfSchemaFloatRange},
	{"IntRange", gmfSchemaIntRange},
	{"NumRange", gmfSchemaNumRange},
};

//////////////////////////////////////////////////////////////////////////

#define array_size(ar) sizeof(ar)/sizeof(ar[0])

void gmBindSchemaLib(gmMachine * a_machine)
{
	a_machine->RegisterLibrary(s_schemaLib,array_size(s_schemaLib));
	a_machine->RegisterLibrary(s_createElementLib,array_size(s_createElementLib),"Validate");

	GM_SCHEMA = a_machine->CreateUserType("Schema");
	a_machine->RegisterTypeLibrary(GM_SCHEMA, s_schemaTypeLib, array_size(s_schemaTypeLib));
	a_machine->RegisterUserCallbacks(GM_SCHEMA,gmfTraceSchema,NULL,NULL,NULL);
	a_machine->RegisterTypeOperator(GM_SCHEMA, O_GETDOT, NULL, gmSchemaGetDot);
	a_machine->RegisterTypeOperator(GM_SCHEMA, O_SETDOT, NULL, gmSchemaSetDot);

	GM_SCHEMA_ELEMENT = a_machine->CreateUserType("SchemaElement");
	a_machine->RegisterTypeLibrary(GM_SCHEMA_ELEMENT, s_schemaElementTypeLib, array_size(s_schemaElementTypeLib));
	a_machine->RegisterUserCallbacks(GM_SCHEMA_ELEMENT,gmfTraceSchemaElement,NULL,NULL,NULL);
}
