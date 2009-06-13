//////////////////////////////////////////////////////////////////////////
// gmbinder - by Jeremy Swigart
//
// This class provides a simple way to bind native classes to custom script types
//
// Features:
//		Bind classes to script, control whether script can create an instance or not.
//		Bind class variables to script. 
//			Supports bool,int,float,const char *,std::string,gmTableObject,gmFunctionObject,
//		Bind static functions to script(up to 9 parameters). No glue function needed.
//		Bind member functions to script(up to 9 parameters). No glue function needed.
//		Bind class constants to script. Access through an instance currently.
//
// Unsupported Features:
//		Automatic binding of overloaded functions. Overloaded functions must be bound to
//			multiple script functions.
//		Ex: If your class had: void DoSomething(int) and void DoSomething(float)
//			you could bind both functions, but using different names for each script.
//		Variable argument functions. To support variable arguments you must use one of the 
//			raw binding functions.
//////////////////////////////////////////////////////////////////////////

#ifndef _GMBINDER2_CLASS_H_
#define _GMBINDER2_CLASS_H_

#include <string>
#include <map>

namespace gmBind2
{
	//////////////////////////////////////////////////////////////////////////
	template <typename ClassT>
	class ClassBase
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		typedef void (*pfnAsStringCallback)(ClassT *a_var, char * a_buffer, int a_bufferSize);
		typedef void (*pfnTraceCallback)(ClassT *a_var, gmMachine * a_machine, gmGarbageCollector* a_gc, const int a_workLeftToGo, int& a_workDone);

		typedef bool (*pfnSetDotEx)(gmThread * a_thread, ClassT *a_var, const char *a_key, gmVariable * a_operands);
		typedef bool (*pfnGetDotEx)(gmThread * a_thread, ClassT *a_var, const char *a_key, gmVariable * a_operands);
		//////////////////////////////////////////////////////////////////////////

		static gmType ClassType()		{ return m_ClassType; }
		static const char *ClassName()	{ return m_ClassName; }
		static bool IsExtensible()			{ return m_Extensible; }

		ClassBase(const char *a_classname, gmMachine *a_machine, bool _extensible)
		{
			GM_ASSERT(!m_ClassName && !m_ClassType);
			{
				m_Machine = a_machine;
				m_ClassName = a_classname;
				m_ClassType = a_machine->CreateUserType(a_classname);
				m_Extensible = _extensible;

				m_Machine->RegisterUserCallbacks(ClassType(), 
					gmfTraceObject, 
					gmfGarbageCollect, 
					gmfAsStringCallback); 
			}
		}
	protected:
		static gmType		m_ClassType;
		static const char	*m_ClassName;

		static bool			m_Extensible;

		gmMachine			*m_Machine;

		static pfnAsStringCallback		m_AsStringCallback;
		static pfnTraceCallback			m_TraceCallback;

		static pfnSetDotEx m_SetDotEx;
		static pfnGetDotEx m_GetDotEx;

		static int gmfDefaultConstructor(gmThread *a_thread)
		{
			BoundObject<ClassT> *bo = new BoundObject<ClassT>(new ClassT());
			if(ClassBase<ClassT>::IsExtensible())
				bo->m_Table = a_thread->GetMachine()->AllocTableObject();
			a_thread->PushNewUser(bo, ClassType());
			return GM_OK;
		}
		static int gmfArgConstructor(gmThread *a_thread)
		{
			BoundObject<ClassT> *bo = new BoundObject<ClassT>(new ClassT(a_thread));
			if(ClassBase<ClassT>::IsExtensible())
				bo->m_Table = a_thread->GetMachine()->AllocTableObject();
			a_thread->PushNewUser(bo, ClassType());
			return GM_OK;
		}
		static void gmfGarbageCollect(gmMachine *a_machine, gmUserObject *a_object)
		{
			GM_ASSERT(a_object->m_userType == m_ClassType);
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_object->m_user);
			if(bo->m_NativeObj && !bo->IsNative())
			{
				delete bo->m_NativeObj;
				bo->m_NativeObj = NULL;
			}
			delete bo;
			a_object->m_user = NULL;
		}
		static bool gmfTraceObject(gmMachine *a_machine, gmUserObject*a_object, gmGarbageCollector*a_gc, const int a_workLeftToGo, int& a_workDone)
		{
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_object->m_user);
			if(bo && bo->m_Table)
				a_gc->GetNextObject(bo->m_Table);
			if(bo && bo->m_NativeObj)
			{
				if(ClassBase<ClassT>::m_TraceCallback)
					ClassBase<ClassT>::m_TraceCallback(bo->m_NativeObj, a_machine, a_gc, a_workLeftToGo, a_workDone);
			}
			a_workDone += 2;
			return true;
		}
		static void gmfAsStringCallback(gmUserObject * a_object, char * a_buffer, int a_bufferSize)
		{
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_object->m_user);
			if(bo && bo->m_NativeObj)
			{
				if(ClassBase<ClassT>::m_AsStringCallback)
					ClassBase<ClassT>::m_AsStringCallback(bo->m_NativeObj, a_buffer, a_bufferSize);
				else
					_gmsnprintf(a_buffer, a_bufferSize, "%X", bo->m_NativeObj);
			}
		}
		/*static void gmfDebugChildInfoCallback(gmUserObject *a_object, gmMachine *a_machine, gmChildInfoCallback a_infoCallback)
		{
		ClassT *pNative = static_cast<ClassT*>(a_object->m_user);
		if(pNative)
		{
		}
		}*/
	};

	template <typename ClassT>
	gmType ClassBase<ClassT>::m_ClassType = GM_NULL;

	template <typename ClassT>
	const char *ClassBase<ClassT>::m_ClassName = 0;

	template <typename ClassT>
	bool ClassBase<ClassT>::m_Extensible = false;

	template <typename ClassT>
	typename ClassBase<ClassT>::pfnAsStringCallback ClassBase<ClassT>::m_AsStringCallback = 0;

	template <typename ClassT>
	typename ClassBase<ClassT>::pfnTraceCallback ClassBase<ClassT>::m_TraceCallback = 0;

	template <typename ClassT>
	typename ClassBase<ClassT>::pfnGetDotEx ClassBase<ClassT>::m_GetDotEx = 0;
	template <typename ClassT>
	typename ClassBase<ClassT>::pfnSetDotEx ClassBase<ClassT>::m_SetDotEx = 0;	

	//////////////////////////////////////////////////////////////////////////
	template <typename ClassT>
	class Class : public ClassBase<ClassT>
	{
	public:
		template <typename Fn>
		Class &func(Fn a_fn, const char *a_funcname)
		{
			typedef typename FunctionTraits<Fn>::Class_Type cls_type;
			GM_ASSERT(ClassBase<cls_type>::ClassType() != GM_NULL);

			gmFunctionEntry fn = {0,0,0};
			fn.m_name = a_funcname;
			fn.m_function = 0;
			fn.m_functor = new GMExportFunctor<Fn>(a_fn);
			ClassBase<ClassT>::m_Machine->RegisterTypeLibrary(ClassBase<ClassT>::ClassType(), &fn, 1);
			return *this;
		}
		Class &func(RawFunctionType a_fn, const char *a_funcname)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name = a_funcname;
			fn.m_function = a_fn;
			fn.m_functor = 0;
			ClassBase<ClassT>::m_Machine->RegisterTypeLibrary(ClassBase<ClassT>::ClassType(), &fn, 1);
			return *this;
		}
		template <typename Fn>
		Class &func_operator(gmOperator a_op, Fn a_fn)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name = 0;
			fn.m_function = 0;
			fn.m_functor = new GMExportOpFunctor<Fn>(a_fn);
			ClassBase<ClassT>::m_Machine->RegisterTypeOperator(ClassBase<ClassT>::ClassType(), a_op, NULL, NULL, &fn);
			return *this;
		}
		Class &rawfunc_operator(gmOperator a_op, RawFunctionType a_fn)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name = 0;
			fn.m_function = a_fn;
			fn.m_functor = 0;
			ClassBase<ClassT>::m_Machine->RegisterTypeOperator(ClassBase<ClassT>::ClassType(), a_op, NULL, NULL, &fn);
			return *this;
		}

		template<typename VarType>
		Class &var(VarType ClassT::* _var, const char *_name)
		{
			struct CV { VarType ClassT::* var; } cv; // Cast Variable helper.
			cv.var = _var;

			gmPropertyFunctionPair pr;
			pr.m_Getter = GMProperty::Get<VarType>;
			pr.m_Setter = GMProperty::Set<VarType>;
			pr.m_PropertyOffset = (size_t)(*(VarType**)&cv);
			pr.m_Static = false;
			m_Properties.insert(std::make_pair(_name, pr));
			return *this;
		}
		template<typename VarType>
		Class &var(VarType * _var, const char *_name)
		{
			gmPropertyFunctionPair pr;
			pr.m_Getter = GMProperty::Get<VarType>;
			pr.m_Setter = GMProperty::Set<VarType>;
			pr.m_PropertyOffset = (size_t)(_var);
			pr.m_Static = true;
			m_Properties.insert(std::make_pair(_name, pr));
			return *this;
		}	
		template<typename VarType>
		Class &var_readonly(VarType ClassT::* _var, const char *_name)
		{
			struct CV { VarType ClassT::* var; } cv; // Cast Variable helper.
			cv.var = _var;

			gmPropertyFunctionPair pr;
			pr.m_Getter = GMProperty::Get<VarType>;
			//pr.m_Setter = GMProperty::Get<VarType>;
			pr.m_PropertyOffset = (size_t)(*(VarType**)&cv);
			pr.m_Static = false;
			m_Properties.insert(std::make_pair(_name, pr));
			return *this;
		}
		template<typename VarType>
		Class &var_bitfield(VarType ClassT::* _var, int _bit, const char *_name)
		{
			struct CV { VarType ClassT::* var; } cv; // Cast Variable helper.
			cv.var = _var;

			gmPropertyFunctionPair pr;
			pr.m_Getter = GMProperty::GetBitField<VarType>;
			pr.m_Setter = GMProperty::SetBitField<VarType>;
			pr.m_PropertyOffset = (size_t)(*(int**)&cv);
			pr.m_BitfieldOffset = _bit;
			pr.m_Static = false;
			m_Properties.insert(std::make_pair(_name, pr));
			return *this;
		}
		Class &constructor(RawFunctionType f, const char *_name = 0, const char *_undertable = 0)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name =  _name ? _name : ClassBase<ClassT>::ClassName();
			fn.m_function = f;
			ClassBase<ClassT>::m_Machine->RegisterLibrary(&fn, 1, _undertable, false);
			return *this;
		}
		Class &constructor(const char *_name = 0, const char *_undertable = 0)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name =  _name ? _name : ClassBase<ClassT>::ClassName();
			fn.m_function = ClassBase<ClassT>::gmfDefaultConstructor;
			fn.m_functor = 0;
			ClassBase<ClassT>::m_Machine->RegisterLibrary(&fn, 1, _undertable, false);
			return *this;
		}
		Class &constructorArgs(const char *_name = 0, const char *_undertable = 0)
		{
			gmFunctionEntry fn = {0,0,0};
			fn.m_name =  _name ? _name : ClassBase<ClassT>::ClassName();
			fn.m_function = ClassBase<ClassT>::gmfArgConstructor;
			fn.m_functor = 0;
			ClassBase<ClassT>::m_Machine->RegisterLibrary(&fn, 1, _undertable, false);
			return *this;
		}
		Class &asString(typename ClassBase<ClassT>::pfnAsStringCallback f)
		{
			ClassBase<ClassT>::m_AsStringCallback = f;
			return *this;
		}
		Class &trace(typename ClassBase<ClassT>::pfnTraceCallback f)
		{
			ClassBase<ClassT>::m_TraceCallback = f;
			return *this;
		}
		Class &getDotEx(typename ClassBase<ClassT>::pfnGetDotEx f)
		{
			GM_ASSERT(ClassBase<ClassT>::ClassType()!=GM_NULL);
			ClassBase<ClassT>::m_GetDotEx = f;
			return *this;
		}
		Class &setDotEx(typename ClassBase<ClassT>::pfnSetDotEx f)
		{
			GM_ASSERT(ClassBase<ClassT>::ClassType()!=GM_NULL);
			ClassBase<ClassT>::m_SetDotEx = f;
			return *this;
		}
		template<class BaseClassT> 
		Class &base()
		{
			GM_ASSERT(ClassBase<BaseClassT>::ClassType()!=GM_NULL);

			ClassBase<ClassT>::m_Machine->SetBaseForType(
				ClassBase<ClassT>::ClassType(), 
				ClassBase<BaseClassT>::ClassType());
			return *this;
		}
		//////////////////////////////////////////////////////////////////////////
		static gmGCRoot<gmUserObject> WrapObject(gmMachine *a_machine, ClassT *a_instance, bool a_native = true)
		{
			if(a_instance && ClassBase<ClassT>::ClassType() != GM_NULL)
			{
				BoundObject<ClassT> *bo = new BoundObject<ClassT>(a_instance);
				if(ClassBase<ClassT>::IsExtensible())
					bo->m_Table = a_machine->AllocTableObject();
				bo->SetNative(a_native);
				return gmGCRoot<gmUserObject>(
					a_machine->AllocUserObject(bo, ClassBase<ClassT>::ClassType()),a_machine);
			}
			return gmGCRoot<gmUserObject>();
		}
		static void NullifyUserObject(gmGCRoot<gmUserObject> a_userObj)
		{
			if(a_userObj)
			{
				GM_ASSERT(a_userObj->GetType() == ClassBase<ClassT>::ClassType());
				BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(((gmUserObject*)a_userObj)->m_user);
				GM_ASSERT(bo && bo->IsNative());
				if(!bo->IsNative())
					delete bo->m_NativeObj;
				bo->m_NativeObj = NULL;
			}
		}
		static BoundObject<ClassT>*GetBoundObject(gmGCRoot<gmUserObject> a_userObj)
		{
			if(a_userObj)
			{
				GM_ASSERT(a_userObj->GetType() == ClassBase<ClassT>::ClassType());
				BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(((gmUserObject*)a_userObj)->m_user);
				return bo;
			}
			return NULL;
		}
		static gmTableObject*GetTable(gmGCRoot<gmUserObject> a_userObj)
		{
			if(a_userObj)
			{
				GM_ASSERT(a_userObj->GetType() == ClassBase<ClassT>::ClassType());
				BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(((gmUserObject*)a_userObj)->m_user);
				return bo->m_Table;
			}
			return NULL;
		}
		static void CloneTable(gmMachine *a_machine, gmGCRoot<gmUserObject> a_userObj, gmGCRoot<gmUserObject> a_cloneTo)
		{
			BoundObject<ClassT> *boFrom = GetBoundObject(a_userObj);
			BoundObject<ClassT> *boTo = GetBoundObject(a_cloneTo);
			GM_ASSERT(boFrom && boTo);
			if(boFrom && boTo)
			{
				if(boFrom->m_Table)
				{
					boTo->m_Table = boFrom->m_Table->Duplicate(a_machine);
				}				
			}
		}
		static bool FromParam(gmThread *a_thread, int a_param, ClassT *&a_instance)
		{
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_thread->ParamUserCheckType(
				a_param, 
				ClassBase<ClassT>::ClassType()));
			if(bo)
			{
				a_instance = bo->m_NativeObj;
				return true;
			}
			return false;
		}
		static bool FromThis(gmThread *a_thread, ClassT *&a_instance)
		{
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_thread->ThisUserCheckType(
				ClassBase<ClassT>::ClassType()));
			if(bo)
			{
				a_instance = bo->m_NativeObj;
				return true;
			}
			return false;
		}
		static bool FromVar(gmThread *a_thread, gmVariable &a_var, ClassT *&a_instance)
		{
			gmUserObject *userObj = a_var.GetUserObjectSafe(ClassBase<ClassT>::ClassType());
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(userObj?userObj->m_user:0);
			if(bo)
			{
				a_instance = bo->m_NativeObj;
				return true;
			}
			return false;
		}
		static void PushObject(gmThread *a_thread, ClassT *a_instance, bool a_native = false)
		{
			if(a_instance && ClassBase<ClassT>::ClassType() != GM_NULL)
			{
				BoundObject<ClassT> *bo = new BoundObject<ClassT>(a_instance);
				if(ClassBase<ClassT>::IsExtensible())
					bo->m_Table = a_thread->GetMachine()->AllocTableObject();
				bo->SetNative(a_native);
				a_thread->PushNewUser(bo, ClassBase<ClassT>::ClassType());
			}
		}
		//////////////////////////////////////////////////////////////////////////
		Class(const char *_classname, gmMachine *_machine, bool _extensible = true) : ClassBase<ClassT>(_classname, _machine,_extensible)
		{
			GM_ASSERT(m_ClassType!=GM_NULL);

			_machine->RegisterTypeOperator( ClassBase<ClassT>::ClassType(), O_GETDOT, NULL, gmBind2OpGetDot);
			_machine->RegisterTypeOperator( ClassBase<ClassT>::ClassType(), O_SETDOT, NULL, gmBind2OpSetDot);
#if GM_BOOL_OP
			_machine->RegisterTypeOperator( ClassBase<ClassT>::ClassType(), O_BOOL, NULL, gmBind2OpBool);
#endif
		}

	private:
		//////////////////////////////////////////////////////////////////////////
		typedef int (*gmBindProp)(void *p, gmThread * a_thread, gmVariable * a_operands, size_t a_offset, size_t a_bit, bool a_static);
		struct gmPropertyFunctionPair
		{
			gmBindProp	m_Getter;
			gmBindProp	m_Setter;
			size_t		m_PropertyOffset;
			size_t		m_BitfieldOffset;
			bool		m_Static;
			gmPropertyFunctionPair() : m_Getter(0), m_Setter(0), m_PropertyOffset(0), m_BitfieldOffset(0) { }
		};

		typedef std::map<std::string, gmPropertyFunctionPair> PropertyMap;
		static PropertyMap m_Properties;

		static void GM_CDECL gmBind2OpGetDot(gmThread * a_thread, gmVariable * a_operands)
		{
			// Ensure the operation is being performed on our type
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_operands[0].GetUserSafe(ClassBase<ClassT>::ClassType()));
			GM_ASSERT(bo);
			if(!bo || !bo->m_NativeObj)
			{
				a_operands[0].Nullify();
				return;
			}

			const char *pString = a_operands[1].GetCStringSafe();
			if(pString)
			{
				// custom handler defined?
				if(ClassBase<ClassT>::m_GetDotEx && 
					ClassBase<ClassT>::m_GetDotEx(a_thread,bo->m_NativeObj,pString,a_operands))
				{
					return;
				}

				typename Class<ClassT>::PropertyMap::iterator it = m_Properties.find(pString);
				if(it != m_Properties.end())
				{
					gmPropertyFunctionPair &propfuncs = it->second;
					if(propfuncs.m_Getter)
					{
						propfuncs.m_Getter(
							bo->m_NativeObj, 
							a_thread, 
							a_operands, 
							propfuncs.m_PropertyOffset, 
							propfuncs.m_BitfieldOffset,
							propfuncs.m_Static);
						return;
					}
				}
				else
				{
					if(bo->m_Table)
					{
						a_operands[0] = bo->m_Table->Get(a_thread->GetMachine(),pString);
						return;
					}
				}
			}
			a_operands[0].Nullify();
		}
		
		static void GM_CDECL gmBind2OpSetDot(gmThread * a_thread, gmVariable * a_operands)
		{
			// Ensure the operation is being performed on our type
			BoundObject<ClassT> *bo = static_cast<BoundObject<ClassT>*>(a_operands[0].GetUserSafe(ClassBase<ClassT>::ClassType()));
			GM_ASSERT(bo);
			if(!bo || !bo->m_NativeObj)
			{
				a_operands[0].Nullify();
				return;
			}

			const char *pString = a_operands[2].GetCStringSafe();
			if(pString)
			{
				// custom handler defined?
				if(ClassBase<ClassT>::m_SetDotEx && 
					ClassBase<ClassT>::m_SetDotEx(a_thread,bo->m_NativeObj,pString,a_operands))
				{
					return;
				}

				typename Class<ClassT>::PropertyMap::iterator it = m_Properties.find(pString);
				if(it != m_Properties.end())
				{
					gmPropertyFunctionPair &propfuncs = it->second;
					if(propfuncs.m_Setter)
					{
						propfuncs.m_Setter(
							bo->m_NativeObj, 
							a_thread, 
							a_operands, 
							propfuncs.m_PropertyOffset, 
							propfuncs.m_BitfieldOffset,
							propfuncs.m_Static);
						return;
					}
				}
					else
					{
					if(bo->m_Table)
						{
						bo->m_Table->Set(a_thread->GetMachine(),pString,a_operands[1]);
						return;
					}
				}
			}
			a_operands[0].Nullify();
		}
		static void GM_CDECL gmBind2OpBool(gmThread * a_thread, gmVariable * a_operands)
		{
			a_operands[0].SetInt(a_operands[0].GetUserSafe(ClassBase<ClassT>::ClassType()) ? 1 : 0);
		}
	};

	template <typename ClassT>
	typename Class<ClassT>::PropertyMap Class<ClassT>::m_Properties;

	//////////////////////////////////////////////////////////////////////////
};

#endif
