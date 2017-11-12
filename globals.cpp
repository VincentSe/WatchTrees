/*++

Copyright (c) 2017  Vincent Semeria

--*/

#include "globals.h"

#define KDEXT_64BIT 
// Structures that describe structures (fPointer, fStruct, fArray, ...)
#include "wdbgexts.h"


WINDBG_EXTENSION_APIS   ExtensionApis;

// Global variables to call CDB
PDEBUG_CONTROL        g_ExtControl = 0;
PDEBUG_SYMBOLS2       g_ExtSymbols = 0;
IDebugAdvanced2*	  g_ExtAdvanced = 0;
IDebugSystemObjects*  g_ExtSystem = 0;

void DestroyDebuggerGlobals()
{
	g_ExtControl->Release(); g_ExtControl = 0;
	g_ExtSymbols->Release(); g_ExtSymbols = 0;
	g_ExtAdvanced->Release(); g_ExtAdvanced = 0;
	g_ExtSystem->Release(); g_ExtSystem = 0;
}

HRESULT InitDebuggerGlobals(PDEBUG_CLIENT4 Client)
{
	HRESULT Status;

	if ((Status = Client->QueryInterface(__uuidof(IDebugControl),
		(void **)&g_ExtControl)) != S_OK)
	{
		goto Fail;
	}
	if ((Status = Client->QueryInterface(__uuidof(IDebugSymbols2),
		(void **)&g_ExtSymbols)) != S_OK)
	{
		goto Fail;
	}
	if ((Status = Client->QueryInterface(__uuidof(IDebugAdvanced2),
		(void **)&g_ExtAdvanced)) != S_OK)
	{
		goto Fail;
	}
	if ((Status = Client->QueryInterface(__uuidof(IDebugSystemObjects),
		(void **)&g_ExtSystem)) != S_OK)
	{
		goto Fail;
	}

	return S_OK;

Fail:
	DestroyDebuggerGlobals();
	return Status;
}

NativeDbgEngAPIManager::NativeDbgEngAPIManager(PDEBUG_CLIENT4 client)
{
	this->initialized = (S_OK == InitDebuggerGlobals(client));
}

NativeDbgEngAPIManager::~NativeDbgEngAPIManager()
{
	DestroyDebuggerGlobals();
}

extern "C"
HRESULT
CALLBACK
DebugExtensionInitialize(PULONG Version, PULONG Flags)
{
	IDebugClient *DebugClient;
	PDEBUG_CONTROL DebugControl;
	HRESULT Hr;

	*Version = DEBUG_EXTENSION_VERSION(1, 0);
	*Flags = 0;
	Hr = S_OK;

	// DebugCreate requires a link to dbgeng.dll, try to remove it : Client is provided to each CDB extension method as an argument
	if ((Hr = DebugCreate(__uuidof(IDebugClient), (void **)&DebugClient)) != S_OK)
	{
		return Hr;
	}

	if ((Hr = DebugClient->QueryInterface(__uuidof(IDebugControl),
		(void **)&DebugControl)) == S_OK)
	{

		//
		// Get the windbg-style extension APIS
		//
		ExtensionApis.nSize = sizeof(ExtensionApis);
		Hr = DebugControl->GetWindbgExtensionApis64(&ExtensionApis);

		//DebugControl->Execute(DEBUG_OUTCTL_ALL_CLIENTS |
		//	DEBUG_OUTCTL_OVERRIDE_MASK |
		//	DEBUG_OUTCTL_NOT_LOGGED,
		//	"sxd -c \"!HandleCLRNotification\" clrn",
		//	DEBUG_EXECUTE_DEFAULT);

		DebugControl->Release();

	}

	CoInitializeEx(0, 0);
	DebugClient->Release();
	return Hr;
}

extern "C"
void
CALLBACK
DebugExtensionUninitialize(void)
{
	return;
}
