/*++

Copyright (c) 2017  Vincent Semeria

--*/


/**
	Stepping and breakpoint commands for managed (.NET) code.

	They are missing from SOS.dll : managed steps in the source code, evaluate a managed variable name.
*/

// C:\Windows\Microsoft.NET\Framework64\v4.0.30319\sos.dll and clr.dll

#include <DbgEng.h>
#include "globals.h"
#include "CLRInterfaces.h"
#include <stdio.h>

#define KDEXT_64BIT 
#include "wdbgexts.h"

IXCLRDataProcess*& GetIClr()
{
	static IXCLRDataProcess* iClr = 0;
	return iClr;
}

ISOSDacInterface*& GetIClr3()
{
	static ISOSDacInterface* iClr3 = 0;
	return iClr3;
}

void init_clr_interfaces()
{
	// clr.dll must be loaded in CDB before calling this, otherwise it will return
	// corrupted pointers as sucess.

	WDBGEXTS_CLR_DATA_INTERFACE ixDataQuery;
	IXCLRDataProcess*& iClr = GetIClr();
	ULONG res;
	if (!iClr)
	{
		ixDataQuery.Iid = &__uuidof(IXCLRDataProcess);
		res = Ioctl(IG_GET_CLR_DATA_INTERFACE, &ixDataQuery, sizeof(ixDataQuery));
		iClr = res ? (IXCLRDataProcess*)ixDataQuery.Iface : 0;
	}
	ISOSDacInterface*& iClr3 = GetIClr3();
	if (!iClr3)
	{
		ixDataQuery.Iid = &__uuidof(ISOSDacInterface);
		res = Ioctl(IG_GET_CLR_DATA_INTERFACE, &ixDataQuery, sizeof(ixDataQuery));
		iClr3 = res ? (ISOSDacInterface*)ixDataQuery.Iface : 0;
	}
}

void reset_clr_interfaces()
{
	// For example, when a method is jitted, old CLR interfaces
	// become corrupt.

	IXCLRDataProcess*& iClr = GetIClr();
	if (iClr)
	{
		iClr->Release();
		iClr = 0;
	}
	ISOSDacInterface*& iClr3 = GetIClr3();
	if (iClr3)
	{
		iClr3->Release();
		iClr3 = 0;
	}
	init_clr_interfaces();
}


class ManagedBreakpoint
{
public:
	ManagedBreakpoint()
	{
		address = 0;
		*module = 0;
		*file = 0;
		*function = 0;
		line = 0;
		child = 0;
		requestedId = 0;
	}
	ManagedBreakpoint(char* module, char* file, char* function, ULONG line)
	{
		address = 0;
		strcpy_s(this->module, 256, module);
		strcpy_s(this->file, 256, file);
		strcpy_s(this->function, 256, function);
		this->line = line;
		child = 0;
	}

	void Add(ManagedBreakpoint* child)
	{
		ManagedBreakpoint* bro = this->child;
		this->child = child;
		child->child = bro;
	}

	void Remove(ManagedBreakpoint* bp)
	{
		ManagedBreakpoint* it = this;
		while (it->child)
		{
			if (bp == it->child)
			{
				ManagedBreakpoint* del = it->child;
				it->child = it->child->child;
				delete del;
				return;
			}
			it = it->child;
		}
	}

	ManagedBreakpoint* Find(char* function)
	{
		ManagedBreakpoint* bp = this;
		while (bp)
		{
			if (strcmp(bp->function, function) == 0)
				return child;
			bp = bp->child;
		}
		return 0;
	}

	ULONG64 address; // native address to break
	char module[256];
	char file[256];
	char function[256];
	ULONG line;
	ULONG requestedId;
	ManagedBreakpoint* child;
};

ManagedBreakpoint gPendingBreakpointList; // waiting for their functions to be jitted


HRESULT sourceCode2ip(const char* moduleName,
	const char* fileName,
	/*in out*/ char* functionName, // optional, including class for managed functions, overwritten with complete name
	ULONG line,
	/*out*/ ULONG64* ip,
	/*out*/ bool* managed)
{
	IXCLRDataProcess* iClr = GetIClr();
	*managed = false;
	*ip = 0;

	// Loaded module names can be different from their DLLs (. replaced by _, offset added)
	ULONG loadedModules, unloadedModules;
	g_ExtSymbols->GetNumberModules(&loadedModules, &unloadedModules);

	char ImageNameBuffer[256];
	char ModuleNameBuffer[256];
	ULONG i, imageNameLength;
	size_t modNameLength = strlen(moduleName);
	for (i = 0; i < loadedModules; i++)
	{
		g_ExtSymbols->GetModuleNames(i, //_In_ ULONG Index,
			0, //_In_ ULONG64 Base,
			ImageNameBuffer, 256, &imageNameLength,
			ModuleNameBuffer, 256, 0,
			0, 0, 0);
		if (imageNameLength >= modNameLength + 5
			&& strncmp(ImageNameBuffer + (imageNameLength - modNameLength - 5), // skip ".dll"
				moduleName, modNameLength) == 0)
			break;
	}
	if (i == loadedModules)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "sourceCode2ip, DLL %s not loaded.\n", moduleName);
		return E_FAIL;
	}


	ULONG64 modBase = 0;
	if (g_ExtSymbols->GetModuleByIndex(i, /*out*/&modBase) != S_OK)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "sourceCode2ip, module %s not found.\n", moduleName);
		return E_FAIL;
	}
	g_ExtSymbols->GetNameByOffset(modBase, 0, 0, 0, 0); // load its PDB if needed

	if (g_ExtSymbols->GetOffsetByLine(line, fileName, /*out*/ip) != S_OK
		&& g_ExtSymbols->GetOffsetByLine(line + 1, fileName, /*out*/ip) != S_OK
		&& g_ExtSymbols->GetOffsetByLine(line + 2, fileName, /*out*/ip) != S_OK)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "sourceCode2ip, failed to get IP %s %d\n", fileName, line);
		return E_FAIL;
	}
	//dprintf("native address %p\n", *ip);

	ULONG64 ilDispl;
	char nativeFunction[256];
	g_ExtSymbols->GetNameByOffset(*ip,
		nativeFunction, 256,
		0,
		&ilDispl);

	if (!strstr(functionName, "."))
	{
		// interpret functionName as the name of the class
		strcat(functionName, ".");
		char* tok = strtok(nativeFunction, "!");
		tok = strtok(0, "+");
		strcat(functionName, tok);
		//		dprintf("managed func name %s\n", functionName);
	}

	IXCLRDataModule* clrModule = 0;
	if (iClr->GetModuleByAddress(*ip, &clrModule) != S_OK)
	{
		//CLRDATA_ENUM hdl = 0;
		//iClr->lpVtbl->StartEnumModules(iClr, &hdl);
		//while (iClr->lpVtbl->EnumModule(iClr, &hdl, &clrModule) == S_OK)
		//{
		//	WCHAR clrName[256];
		//	clrModule->lpVtbl->GetName(clrModule, 256, 0, clrName);
		//	wcstombs(ModuleNameBuffer, clrName, 256);
		//	if (strcmp(ModuleNameBuffer, moduleName) == 0)
		//		break;
		//	clrModule->lpVtbl->Release(clrModule);
		//}
		//iClr->lpVtbl->EndEnumModules(iClr, hdl);

		return E_FAIL; // maybe not jitted yet ?
	}

	WCHAR functionW[256];
	*functionW = 0;
	mbstowcs(functionW, functionName, 256);

	CLRDATA_ENUM hdl = 0, hdl2 = 0;
	IXCLRDataMethodDefinition* clrMethod = 0; // when jitted it'll have instances
	IXCLRDataMethodInstance* clrMethodInstance = 0;

	// Changing the module changes the function that is notified ?
	//ULONG64 mngMod = 0;
	//clrModule->lpVtbl->Request(clrModule, 0xf0000000, 0, 0, 8, &mngMod); // convert native to managed module ?

	clrModule->StartEnumMethodDefinitionsByName(functionW, 0, &hdl);
	if (clrModule->EnumMethodDefinitionByName(&hdl, &clrMethod) == S_OK)
	{
		*managed = true;
		clrMethod->GetName(0, 256, 0, functionW);
		wcstombs(functionName, functionW, 256);

		if (clrMethod->StartEnumInstances(0, &hdl2) != S_OK)
		{
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Method %s not found. Maybe not jitted yet.\n", functionName);
			// clrMethod->lpVtbl->SetCodeNotification(clrMethod, true); // tell the JIT compiler to throw an exception of type clrn when it does this method
			clrMethod->Release();
			clrModule->EndEnumMethodDefinitionsByName(hdl);
			clrModule->Release();
			return S_FALSE;
		}
		clrMethod->EnumInstance(&hdl2, &clrMethodInstance);
		clrMethod->EndEnumInstances(hdl2);

		CLRDATA_ADDRESS_RANGE ip2;
		if (clrMethodInstance->GetAddressRangesByILOffset(
			(ULONG)ilDispl,
			1,
			0, //unsigned int *
			/*out*/ &ip2) != S_OK)
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "failed to get IP\n");

		*ip = ip2.startAddress;

		clrMethod->Release();
	}
	clrModule->EndEnumMethodDefinitionsByName(hdl);
	clrModule->Release();
	return S_OK;
}

/**
	Add a native or managed breakpoint.
*/
HRESULT CALLBACK
mbp(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;
	
	char* tok = strtok((char*)args, " ");
	if (!tok)
	{
		// For example : !mbp testCSharp Program.cs Program.Main 14
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "usage !mbp module file class.function line\n");
		return E_FAIL;
	}

	char module[128];
	strcpy_s(module, 128, tok);

	char file[128];
	tok = strtok(0, " ");
	strcpy_s(file, 128, tok);

	char function[256];
	tok = strtok(0, " ");
	strcpy_s(function, 128, tok);

	ULONG line;
	tok = strtok(0, " ");
	if (!tok)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "mbp: unknown line.\nusage !mbp module file function line\n");
		return E_FAIL;
	}
	sscanf(tok, "%d", &line);

	reset_clr_interfaces();
	IXCLRDataProcess* iClr = GetIClr();
	ISOSDacInterface* iClr3 = GetIClr3();
	DacpUsefulGlobalsData usefulGlobals;
	iClr3->GetUsefulGlobals(&usefulGlobals);

	bool managed;
	ULONG64 ip = 0;
	HRESULT res = sourceCode2ip(module, file, function, line, &ip, &managed);

	if (managed)
	{
		if (res == S_FALSE)
		{
			// remember to add a breakpoint when this method is Jitted
			IXCLRDataModule* clrModule = 0;
			CLRDATA_ENUM hdl = 0, hdl2 = 0;
			iClr->GetModuleByAddress(ip, &clrModule);
			IXCLRDataMethodDefinition* clrMethod = 0;
			WCHAR functionW[256];
			mbstowcs(functionW, function, 256);
			clrModule->StartEnumMethodDefinitionsByName(functionW, 0, &hdl);
			clrModule->EnumMethodDefinitionByName(&hdl, &clrMethod);
			if (clrMethod->StartEnumInstances(0, &hdl2) != S_OK)
				clrMethod->SetCodeNotification(true);
			clrMethod->Release();
			clrModule->Release();

			gPendingBreakpointList.Add(new ManagedBreakpoint(module, file, function, line));
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "adding deferred breakpoint %s %d\n", file, line);
		}
		else
		{
			IDebugBreakpoint* ibp;
			g_ExtControl->AddBreakpoint(DEBUG_BREAKPOINT_CODE,
				DEBUG_ANY_ID,
				&ibp);
			ibp->SetFlags(DEBUG_BREAKPOINT_ENABLED);
			ibp->SetOffset(ip);
		}
	}
	else
	{
		char cmd[256];
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, cmd, "bp `%s!%s:%d`", module, file, line);
		g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE,
			cmd,
			DEBUG_EXECUTE_DEFAULT);
	}

	return S_OK;
}

class ip2ilContext
{
public:
	ip2ilContext(ULONG64 ip, IDebugSymbols3* iSymbols3)
	{
		IXCLRDataProcess* iClr = GetIClr();
		CLRDATA_ENUM hdl = 0;
		IXCLRDataAppDomain* domain = 0;
		HRESULT startEnum = iClr->StartEnumMethodInstancesByAddress(ip, domain, &hdl);
		if (startEnum == S_OK
			&& iClr->EnumMethodInstanceByAddress(&hdl, &meth) == S_OK
			&& iClr->EndEnumMethodInstancesByAddress(hdl) == S_OK)
		{
			ULONG32 mdToken = 0;
			IXCLRDataModule* module = 0;
			if (meth->GetTokenAndScope(/*out*/&mdToken, &module) != S_OK)
				dprintf("GetTokenAndScope failed\n");

			hdl = 0;
			CLRDATA_MODULE_EXTENT outBuf;
			if (module->StartEnumExtents(&hdl) == S_OK
				&& module->EnumExtent(&hdl, &outBuf) == S_OK
				&& module->EndEnumExtents(hdl) == S_OK)
			{
				ULONG64 moduleBaseAddress = outBuf.base;

				DEBUG_MODULE_AND_ID methSymbolId;
				if (iSymbols3->GetSymbolEntryByToken(moduleBaseAddress,
					mdToken,
					&methSymbolId) != S_OK)
				{
					// PDB is not there or could not be associated with the executing code
					//module->lpVtbl->Release(module);
				}

				DEBUG_SYMBOL_ENTRY methSymbol;
				if (iSymbols3->GetSymbolEntryInformation(&methSymbolId, /*out*/ &methSymbol) == S_OK)
					methAddress = methSymbol.Offset;
			}
			module->Release();
		}
	}

	~ip2ilContext()
	{
		if (meth)
			meth->Release();
		meth = 0;
	}

	IXCLRDataMethodInstance* meth = 0;
	ULONG64 methAddress = 0;
};


HRESULT ip2il(ULONG64 ip, /*out*/ PULONG64 ilAddr, /*out*/ WCHAR* managedMethodName, IDebugSymbols3* iSymbols3)
{
	// Convert a native instruction pointer to an MSIL address
	IXCLRDataProcess* iClr = GetIClr();

	if (managedMethodName)
		*managedMethodName = 0;
	// CLRDATA_ADDRESS_TO_TADDR(&ip); seems useless and corrupt in 64 bits

	if (ilAddr)
		*ilAddr = 0;

	ip2ilContext context(ip, iSymbols3);
	if (!context.methAddress)
	{
		//dprintf("first start enum failed on address 0x%p\n", ip);
		//ULONG* ptr = (ULONG*)&ip;
		//*(ptr+1) = 0xffffffff; // ip is 64 bits, set the 32 first ones to ff. Don't know why
		//if (iClr->lpVtbl->StartEnumMethodInstancesByAddress(iClr, ip, domain, &hdl) != S_OK)
		//dprintf("enum method instances failed\n");
		return E_FAIL; // maybe not in managed code
	}

	// At least give the managed method's name
	if (context.meth->GetName(0, 256, 0, /*out*/managedMethodName) != S_OK)
		dprintf("get method name failed\n");

	ULONG32 ilOffset = 0;
	context.meth->GetILOffsetsByAddress(ip, 1, 0, &ilOffset); // != S_OK) // careful to offsets 0xfffffffd and the like

	if (ilAddr)
		*ilAddr = context.methAddress + ilOffset;
	return S_OK;
}

HRESULT WhereIs(ULONG64 instructionPointer,
	/*out*/ char* file,
	/*out*/ PULONG line,
	/*out*/ char* function, // or WCHAR* if function is managed
	bool* managed,
	IXCLRDataProcess* iClr,
	IDebugSymbols3* iSymbols3)
{
	if (file)
		*file = 0;
	function[0] = 0;
	function[1] = 0;
	*line = 0;

	// Test if in managed code first.
	// In core C# functions such as ReadLine, a native symbol in mscorlib
	// will be found, nevertheless the address is managed.
	ULONG64 ilAddr = 0;
	if (ip2il(instructionPointer, /*out*/&ilAddr, /*out*/(WCHAR*)function, iSymbols3) == S_OK)
	{
		*managed = true;
		if (ilAddr)
			g_ExtSymbols->GetLineByOffset(ilAddr, line, file, file ? 1024 : 0, 0, 0);
		return S_OK;
	}

	// Test if in native code
	ULONG cb = 0;
	if (instructionPointer &&
		g_ExtSymbols->GetNameByOffset(instructionPointer,
			/*out*/function,
			1024,
			&cb,
			0) == S_OK
		&& cb>0)
	{
		g_ExtSymbols->GetLineByOffset(instructionPointer, line, file, file ? 1024 : 0, 0, 0); //==S_OK) // find source file and line
		*managed = false;
		return S_OK;
	}

	return E_FAIL;
}

/**
	Go to a stack frame, resolving both native and managed functions.
*/
HRESULT CALLBACK
mframe(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	int frameNumber;
	if (sscanf(args, "%x", &frameNumber) != 1)
	{
		dprintf("usage !mframe number\n");
		return E_FAIL;
	}

	DEBUG_STACK_FRAME frames[32];
	if (g_ExtControl->GetStackTrace(0, 0, 0, frames, 32, 0) != S_OK)
	{
		dprintf("cannot get frame\n");
		return E_FAIL;
	}

	init_clr_interfaces();
	IXCLRDataProcess* iClr = GetIClr();
	IDebugSymbols3* symbols3;
	if (Client->QueryInterface(__uuidof(IDebugSymbols3), (void **)&symbols3) != S_OK)
		dprintf("failed symbols3\n");

	char cmd[256];
	sprintf(cmd, ".frame %d", frameNumber);
	g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE,
		cmd,
		DEBUG_EXECUTE_DEFAULT);

	char file[1024];
	char function[1024];
	bool managed;
	ULONG line;
	WhereIs(frames[frameNumber].InstructionOffset, file, &line, function, &managed, iClr, symbols3);

	if (managed)
	{
		dprintf("%d %p %p XXX!%s+0x00 [%s @ %d]\n",
			frameNumber,
			frames[frameNumber].InstructionOffset,
			frames[frameNumber].StackOffset,
			function,
			file,
			line);
	}
	else
		g_ExtControl->OutputStackTrace(DEBUG_OUTCTL_ALL_CLIENTS |   // Flags on what to do with output
			DEBUG_OUTCTL_OVERRIDE_MASK |
			DEBUG_OUTCTL_NOT_LOGGED,
			frames + frameNumber,
			1,           // number of frames to display
			DEBUG_STACK_SOURCE_LINE | DEBUG_STACK_FRAME_NUMBERS |
			DEBUG_STACK_FRAME_ADDRESSES);

	symbols3->Release();
	return S_OK;
}

/**
	Print call stack, resolving both native and managed functions.
*/
HRESULT CALLBACK
mkpn(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	reset_clr_interfaces(); // get all newly jitted methods
	IXCLRDataProcess* iClr = GetIClr();

	IDebugSymbols3* symbols3;
	if (Client->QueryInterface(__uuidof(IDebugSymbols3), (void **)&symbols3) != S_OK)
		dprintf("failed symbols3\n");


	DEBUG_STACK_FRAME callStack[40];
	ULONG cb, line = 0;
	g_ExtControl->GetStackTrace(0, 0, 0,
		callStack, 40,
		&cb);

	char file[1024] = "";
	char function[1024] = "";
	char function2[512] = "";
	bool managed = false;
	dprintf(" # Child-SP RetAddr  \n");
	for (ULONG i = 0; i<cb; i++)
	{
		WhereIs(callStack[i].InstructionOffset, file, &line, function, &managed, iClr, symbols3);
		if (managed)
		{
			wcstombs(function2, (WCHAR*)function, 512);
			dprintf("%p ", i);
			dprintf("%p %p %s ", callStack[i].StackOffset, callStack[i].ReturnOffset, function2);
			if (line)
				dprintf("[%s @ %d]", file, line);
			dprintf("\n");
		}
		else
			g_ExtControl->OutputStackTrace(DEBUG_OUTCTL_ALL_CLIENTS,
				callStack + i, 1,
				DEBUG_STACK_FRAME_ADDRESSES
				| DEBUG_STACK_SOURCE_LINE
				| DEBUG_STACK_FRAME_NUMBERS
				| DEBUG_STACK_PARAMETERS); // params are not given by WhereIs
	}

	symbols3->Release();
	return S_OK;
}

HRESULT list_managed_breakpoints(IDebugSymbols3* symbols3)
{
	IXCLRDataProcess* iClr = GetIClr();

	ULONG bpCount = 0;
	g_ExtControl->GetNumberBreakpoints(&bpCount);
	char file[256];
	char function[512];
	char functionBis[256];
	ULONG bpId;
	ULONG64 bpAddr;
	ULONG bpFlags;
	char bpCommand[256] = "";
	ULONG line;
	bool managed;
	ULONG maxId = 0;
	for (ULONG i = 0; i<bpCount; i++)
	{
		PDEBUG_BREAKPOINT bp = 0;
		if (g_ExtControl->GetBreakpointByIndex(i, &bp) != S_OK || !bp)
			continue;
		bp->GetOffset(&bpAddr);
		bp->GetFlags(&bpFlags);
		bp->GetId(&bpId);
		if (bpId > maxId)
			maxId = bpId;
		bp->GetCommand(bpCommand, 256, 0);

		// bp->GetOffsetExpression(bpLocation, 256, 0) == S_OK) even native breakpoints don't keep their offset expression
		WhereIs(bpAddr, /*out*/file, /*out*/&line, /*out*/function, /*out*/&managed,
			iClr, symbols3);
		if (managed)
		{
			wcstombs(functionBis, (WCHAR*)function, 256);
			strtok(functionBis, "("); // don't print args
		}
		dprintf(" %d %c %p [%s @ %d] ",
			bpId,
			bpFlags&DEBUG_BREAKPOINT_ENABLED ? 'e' : 'd',
			bpAddr,
			file, line);
		if (managed)
			dprintf("XXX!%s", functionBis);
		else
			dprintf("%s", function);
		if (*bpCommand)
			dprintf(" \"%s\"", bpCommand);
		dprintf("\n");
	}

	maxId++;
	ManagedBreakpoint* bp = gPendingBreakpointList.child;
	while (bp)
	{
		bp->requestedId = maxId;
		dprintf(" %d %c %p ",
			maxId,
			'e',
			0);
		dprintf("[%s @ %d] XXX!", bp->file, bp->line);
		strncpy(function, bp->function, 512);
		strtok(function, "("); // don't print args
		dprintf("%s\n", function);
		bp = bp->child;
		maxId++;
	}

	return S_OK;
}

HRESULT CALLBACK
mbl(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	init_clr_interfaces();
	IDebugSymbols3* symbols3;
	if (Client->QueryInterface(__uuidof(IDebugSymbols3), (void **)&symbols3) != S_OK)
		dprintf("failed symbols3\n");

	list_managed_breakpoints(symbols3);

	symbols3->Release();
	return S_OK;
}

ULONG64 disassembleNextCallAddress(ULONG64 startAddress, bool jump)
{
	char disassBuf[128] = "";
	ULONG flags = 0, instructionCount = 0;
	ULONG64 addr = startAddress;
	char* c = 0;
	while (!c && instructionCount < 200)
	{
		g_ExtControl->Disassemble(
			addr,
			flags,
			/*out*/disassBuf,
			128,
			nullptr,
			/*out*/&addr);
		c = strstr(disassBuf, jump ? " jmp " : " call ");
		instructionCount++;
	}

	char* parenthesis = strstr(c, " (");
	c = parenthesis ? parenthesis + 2 : c + 5; // start of called address
	char* end;
	const ULONG64 callAddr = strtoull(c, /*out*/&end, 16);
	const ULONG64 lowerBits = strtoull(end + 1, /*out*/&end, 16); // skip apostrophe
	return (callAddr << 32) + lowerBits; 
}

void StepComplete(char* stepCommand, ULONG64 startIP, IDebugRegisters* registers)
{
	g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE | DEBUG_OUTCTL_NOT_LOGGED,
		stepCommand,
		DEBUG_EXECUTE_DEFAULT);

	// Wait for step to finish. Before g_ExtControl->Execute, the status was probably already DEBUG_STATUS_BREAK,
	// we must include the line check in the wait test.
	ULONG ulStatus = 0;
	ULONG64 newRip = 0;
	bool stoppedAfterRip = false;
	while (!stoppedAfterRip && ulStatus != DEBUG_STATUS_NO_DEBUGGEE)
	{
		g_ExtControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE);
		g_ExtControl->GetExecutionStatus(&ulStatus);
		stoppedAfterRip = (S_OK == registers->GetInstructionOffset(&newRip) && newRip != startIP && ulStatus == DEBUG_STATUS_BREAK);
	}
}

/**
	Step one line of source code (native or managed).
*/
HRESULT CALLBACK
mp(PDEBUG_CLIENT4 Client, PCSTR args)
{
	char file[1024] = "";
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	const bool stepInto = (*args == 't');

	IDebugSymbols3* symbols3;
	if (Client->QueryInterface(__uuidof(IDebugSymbols3), (void **)&symbols3) != S_OK)
		dprintf("failed symbols3\n");
	IDebugRegisters* registers;
	if (Client->QueryInterface(__uuidof(IDebugRegisters), (void **)&registers) != S_OK)
		dprintf("failed registers\n");

	init_clr_interfaces();
	IXCLRDataProcess* iClr = GetIClr();
	ISOSDacInterface* iClr3 = GetIClr3();

	ULONG64 rip = 0;
	registers->GetInstructionOffset(&rip);
	char initFunction[1024] = "";
	char function[1024] = "";
	bool managed = false;
	ULONG initLine = 0, line = 0;
	WhereIs(rip, 0, &initLine, /*out*/initFunction, &managed, iClr, symbols3);

	if (managed)
	{
		ULONG stepCount = 0;
		if (stepInto)
		{
			PDEBUG_BREAKPOINT bp;
			g_ExtControl->AddBreakpoint(DEBUG_BREAKPOINT_CODE, DEBUG_ANY_ID, /*out*/&bp);
			bp->SetFlags(DEBUG_BREAKPOINT_ENABLED | DEBUG_BREAKPOINT_ONE_SHOT);

			ULONG64 callAddr = disassembleNextCallAddress(rip, false);
			// TODO: if the call instruction is at a different source code line, the step finishes before it.
			// Default to !stepInto

			char disassBuf[128];
			ULONG flags = 0;
			ULONG64 endOffset;
			g_ExtControl->Disassemble(
				callAddr,
				flags,
				/*out*/disassBuf,
				128,
				nullptr,
				&endOffset);

			if (strstr(disassBuf, "call    clr!PrecodeFixupThunk"))
			{
				callAddr = disassembleNextCallAddress(callAddr, false);
				callAddr = disassembleNextCallAddress(callAddr, true); // jump to ThePreStub

				// Find jmp rax, which is where the method will be JIT compiled
				char* c = 0;
				ULONG instructionCount = 0;
				while (!c && instructionCount < 200)
				{
					g_ExtControl->Disassemble(
						callAddr,
						flags,
						/*out*/disassBuf,
						128,
						nullptr,
						/*out*/&callAddr);
					c = strstr(disassBuf, " jmp     rax");
					instructionCount++;
				}

				if (c)
				{
					bp->SetOffset(callAddr - 3);
					//bp->SetCommand("t"); // execute jmp rax
				}
			}
			else
			{
				// the function was already jitted
				bp->SetOffset(callAddr);
			}
			g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE,
				"g",
				DEBUG_EXECUTE_DEFAULT);

			// Wait until bp is hit
			ULONG ulStatus = 0;
			bp->GetOffset(&callAddr);
			bool stoppedAtBP = false;
			ULONG64 rip = 0;
			while (!stoppedAtBP && ulStatus != DEBUG_STATUS_NO_DEBUGGEE)
			{
				g_ExtControl->WaitForEvent(DEBUG_WAIT_DEFAULT, INFINITE);
				g_ExtControl->GetExecutionStatus(&ulStatus);
				registers->GetInstructionOffset(&rip);
				stoppedAtBP = (rip == callAddr && ulStatus == DEBUG_STATUS_BREAK);
			}

			reset_clr_interfaces(); // When a method is jitted, the CLR interfaces become corrupt

			// Step until a managed source code line is found
			g_ExtControl->SetCodeLevel(DEBUG_LEVEL_ASSEMBLY);
			line = 0;
			while (line == 0 && stepCount < 60) // against infinite loops
			{
				StepComplete("t", rip, registers);
				registers->GetInstructionOffset(&rip);

				ULONG64 ilAddr = 0;
				if (ip2il(rip, /*out*/&ilAddr, /*out*/(WCHAR*)function, symbols3) == S_OK && ilAddr)
				{
					g_ExtSymbols->GetLineByOffset(ilAddr, &line, file, file ? 1024 : 0, 0, 0);
				}
				stepCount++;
			}
			g_ExtControl->SetCodeLevel(DEBUG_LEVEL_SOURCE);
			dprintf("%s(%d)+0\n(0) %s\n", file, line, function);
		}
		else
		{
			// Managed step over, don't step into function calls.

			// The source code line does not always increase by execution : end of loops, return of functions, ...
			// We must step in assembler and query the source code until the line changes.
			line = initLine;
			stepCount = 0;
			ip2ilContext context(rip, symbols3); // Managed method at rip
			g_ExtControl->SetCodeLevel(DEBUG_LEVEL_ASSEMBLY);
			while ((line == initLine
				|| (!line && !*function)
				|| (!line && strcmp(function, initFunction) == 0))
				&& stepCount < 60) // against infinite loops
			{
				StepComplete("p", rip, registers);
				registers->GetInstructionOffset(&rip);
				ULONG32 ilOffset = 0;
				context.meth->GetILOffsetsByAddress(rip, 1, 0, &ilOffset);
				g_ExtSymbols->GetLineByOffset(context.methAddress + ilOffset, &line, 0, 0, 0, 0);
				stepCount++;
			}
			g_ExtControl->SetCodeLevel(DEBUG_LEVEL_SOURCE);

			WhereIs(rip, file, &line, function, &managed, iClr, symbols3);
			dprintf("%s(%d)+0\n(0) %s\n", file, line, function);
		}
	}
	else
	{
		// Native step, then print location of instruction pointer
		g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE |
			DEBUG_OUTCTL_NOT_LOGGED,
			stepInto ? "t" : "p",
			DEBUG_EXECUTE_DEFAULT);
		g_ExtControl->Execute(DEBUG_OUTCTL_ALL_CLIENTS |
			DEBUG_OUTCTL_OVERRIDE_MASK |
			DEBUG_OUTCTL_NOT_LOGGED,
			"ln eip",
			DEBUG_EXECUTE_DEFAULT);
	}

	symbols3->Release();
	registers->Release();
	return S_OK;
}
