#include "gmConfig.h"

#if(GM_USE_ENTITY_STACK)

#include "gmEntity.h"
#include "gmThread.h"

//////////////////////////////////////////////////////////////////////////
// Operators

static void gmEntityOpEQ(gmThread * a_thread, gmVariable * a_operands)
{
	if(a_operands[0].m_type == GM_ENTITY && a_operands[1].m_type == GM_ENTITY)
	{
		a_operands[0].SetInt(a_operands[0].m_value.m_enthndl == a_operands[1].m_value.m_enthndl ? 1 : 0);
	}
	else
	{
		a_operands[0].Nullify();
	}
}

void gmEntityOpNEQ(gmThread * a_thread, gmVariable * a_operands)
{
	if(a_operands[0].m_type == GM_ENTITY && a_operands[1].m_type == GM_ENTITY)
	{
		a_operands[0].SetInt(a_operands[0].m_value.m_enthndl != a_operands[1].m_value.m_enthndl ? 1 : 0);
	}
	else
	{
		a_operands[0].Nullify();
	}
}

void gmEntityOpNOT(gmThread * a_thread, gmVariable * a_operands)
{
	if(a_operands[0].m_type == GM_NULL)
		a_operands[0].SetInt(1);
	else
		a_operands[0].SetInt(0);
	a_operands[0].m_type = GM_INT;
}

void gmEntityOpBOOL(gmThread * a_thread, gmVariable * a_operands)
{
	a_operands[0].SetInt(1);
}

void BindEntityStack(gmMachine *a_machine)
{	
	a_machine->RegisterTypeOperator(GM_ENTITY, O_EQ, 0, gmEntityOpEQ);
	a_machine->RegisterTypeOperator(GM_ENTITY, O_NEQ, 0, gmEntityOpNEQ);
	a_machine->RegisterTypeOperator(GM_ENTITY, O_NOT, 0, gmEntityOpNOT);

#if GM_BOOL_OP
	a_machine->RegisterTypeOperator(GM_ENTITY, O_BOOL, 0, gmEntityOpBOOL);
#endif	
}

#endif