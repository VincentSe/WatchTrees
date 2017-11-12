/*++

Copyright (c) 2017  Vincent Semeria

--*/


#ifndef __DBGEXTS_H__
#define __DBGEXTS_H__

// Global variables to query CDB and macros that initialize and destroy them

#include <dbgeng.h>

// Global variables
extern PDEBUG_CONTROL         g_ExtControl;
extern PDEBUG_SYMBOLS2        g_ExtSymbols;
extern IDebugAdvanced2*		  g_ExtAdvanced;
extern IDebugSystemObjects*	  g_ExtSystem;

class NativeDbgEngAPIManager
{
	// Initialize and release the previous global variables

public:
	NativeDbgEngAPIManager(PDEBUG_CLIENT4 Client);
	~NativeDbgEngAPIManager();
	bool initialized;
};

#endif // #ifndef __DBGEXTS_H__
