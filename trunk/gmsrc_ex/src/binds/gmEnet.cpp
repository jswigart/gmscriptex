
#include "gmThread.h"

#include "gmEnet.h"
#include "gmEnetImpl.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////

void gmBindEnet(gmMachine *a_machine)
{
	gmType gmServer = a_machine->CreateUserType("EnetServer");
	gmType gmClient = a_machine->CreateUserType("EnetClient");

}

