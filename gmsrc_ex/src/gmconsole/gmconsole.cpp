#include <iostream>

#include "gmmachine.h"
#include "gmthread.h"
#include "gmdebug.h"
#include "gmstreambuffer.h"

// libs

#include "gmmathlib.h"
#include "gmstringlib.h"
#include "gmarraylib.h"
#include "gmsystemlib.h"
#include "gmvector3lib.h"

#include "timer.h"
#include <math.h>

#undef GetObject

#include "gmbinder2.h"
#include "gmbinder2_class.h"

#define GM_DEBUGGER_PORT  49001

//
// globals
//

#undef GetObject

gmMachine * g_machine = NULL;
Timer g_timer;

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// gmMachine exception handler
//

bool GM_CDECL gmeMachineCallback(gmMachine * a_machine, gmMachineCommand a_command, const void * a_context)
{
	if(a_command == MC_THREAD_EXCEPTION)
	{
		bool first = true;
		const char * entry;
		while((entry = a_machine->GetLog().GetEntry(first)))
		{
			fprintf(stderr, "%s", entry);
		}
		a_machine->GetLog().Reset();
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
//
// main
//
void main(int argc, char * argv[], char * envp[])
{  
	//
	// start the machine
	//

	gmMachine::s_machineCallback = gmeMachineCallback;

	g_machine = new gmMachine;
	g_machine->SetDesiredByteMemoryUsageHard(128*1024);
	g_machine->SetDesiredByteMemoryUsageSoft(g_machine->GetDesiredByteMemoryUsageHard() * 9 / 10);
	g_machine->SetAutoMemoryUsage(true);
	g_machine->SetDebugMode(true);

	std::cout << "gmMachine Created" << std::endl;

	//
	// bind the default libs
	//

	gmBindMathLib(g_machine);
	std::cout << "Lib Bound: Math" << std::endl;
	gmBindStringLib(g_machine);
	std::cout << "Lib Bound: String" << std::endl;
	gmBindArrayLib(g_machine);
	std::cout << "Lib Bound: Array" << std::endl;
	gmBindSystemLib(g_machine);
	std::cout << "Lib Bound: System" << std::endl;
	//gmBindVector3Lib(g_machine);
	//std::cout << "Lib Bound: Vector3" << std::endl;

	//
	// execute loop
	//

	std::cout << "Running Console. Waiting for Input." << std::endl;
	g_timer.Init();

	float timeAcc = 0.0f;
	gmuint32 idt = 0;
	while(1)
	{
		enum { BufferSize=512 };
		char buffer[BufferSize] ={};

		std::cin.getline(buffer,BufferSize);

		//////////////////////////////////////////////////////////////////////////
		char *Script = 0;
		if(strstr(buffer,"runfile"))
		{			
			const char *FileName = buffer+strlen("runfile");
			while(*FileName==' ') ++FileName;
			FILE * fp = fopen(FileName, "rb");
			if(fp)
			{
				fseek(fp, 0, SEEK_END);
				int size = ftell(fp);
				rewind(fp);
				Script = new char[size + 1];
				fread(Script, 1, size, fp);
				Script[size] = 0;
				fclose(fp);
			}
		}
		//////////////////////////////////////////////////////////////////////////
		int errors = g_machine->ExecuteString(Script?Script:buffer, NULL, false);
		if(errors)
		{
			bool first = true;
			const char * message;
			while((message = g_machine->GetLog().GetEntry(first)))
				std::cout << message;
			g_machine->GetLog().Reset();
		}
		delete [] Script;
		Script = 0;

		g_machine->Execute(idt);
		//
		// update time
		//
		timeAcc += (g_timer.Tick() * 1000.0f);
		if(timeAcc > 1.0f)
		{
			idt = (gmuint32) floorf(timeAcc);
			timeAcc -= (float) idt;
		}
		else idt = 0;

	}
#ifdef WIN32
	// Just give the OS a chance to update and run more smoothly.
	Sleep(0);
#endif //WIN32
}

