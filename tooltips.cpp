/*++

Copyright (c) 2017  Vincent Semeria

--*/

#include "globals.h"

#define KDEXT_64BIT 
// Structures that describe structures (fPointer, fStruct, fArray, ...)
#include "wdbgexts.h"


#include <stdio.h>

HRESULT evaluateExpr(const char* expr,
	/*out*/ PSYM_DUMP_PARAM p,
	/*out*/ PULONG64 dynamicDereference);

bool charOfName(char c)
{
	return (c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9')
		|| c == '_' || c == ':';
}

// Get the expression at the given line and column, then do the same as adding a watch to it.
HRESULT CALLBACK
evaluate_tooltip(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	HRESULT res = S_OK;
	//init_clr_interfaces();

	IDebugSystemObjects* sysObj;
	if (Client->QueryInterface(__uuidof(IDebugSystemObjects), (void **)&sysObj) != S_OK)
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "failed system objects\n");

	ULONG linePos;
	char* pch = strtok((char*)args, " ");

	if (!pch || sscanf(pch, "%d", &linePos) != 1)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Usage: %d %s, position tooltip\n");
		res = E_FAIL;
		goto evalTooltipFinish;
	}

	char* tooltipLineStart = pch + strlen(pch) + 1;
	char* s = tooltipLineStart + linePos;
	char* e = tooltipLineStart + linePos;

	// first try to evaluate as large as possible
	while (s > tooltipLineStart)
	{
		if (s[-1] == '>' && s[-2] == '-')
			s -= 2;
		else if (charOfName(s[-1]) || s[-1] == '.')
			s--;
		else
			break;
	}
	while (charOfName(*e))
		e++;

	*e = 0; // maybe save character before erasing it
			//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "tooltip: %s\n", s);

	if (*s == 0)
	{
		res = E_FAIL;
		goto evalTooltipFinish;
	}

	char buf[256] = "?? $!";
	strcat_s(buf, 256, s);

	SYM_DUMP_PARAM p;
	ULONG64 dynamicDereference;
	bool success = true;
	if (evaluateExpr(s,
		&p,
		&dynamicDereference) != S_OK)
	{
		strtok(s, ".");
		char* tok = strtok(0, ".");
		if (tok)
		{
			// try to replace '.' by '->' to handle c++ references
			buf[5] = 0;
			sprintf_s(buf + 5, 251, "%s->%s", s, tok);
			if (evaluateExpr(buf + 5,
				&p,
				&dynamicDereference) != S_OK)
				success = false;
		}
		else
			success = false;
	}

	if (!success)
	{
		res = E_FAIL;
		goto evalTooltipFinish;
	//	// try managed tooltip

	//	DEBUG_STACK_FRAME frame;
	//	g_ExtControl->GetStackTrace(0, 0, 0, &frame, 1, 0);
	//	ClrDataFrame* clrFrame = 0;
	//	if (get_current_managed_frame(/*out*/&clrFrame, sysObj) != S_OK)
	//	{
	//		res = E_FAIL;
	//		goto evalTooltipFinish;
	//	}

	//	IXCLRDataProcess* iClr = GetIClr();
	//	slv_args args;
	//	args.varIdx = 0;
	//	args.varName = s;
	//	args.varFound = false;
	//	enumLocVarNames(frame.InstructionOffset, iClr, &selectLocVar, &args);

	//	if (args.varFound)
	//	{
	//		ClrDataValue* locVar = 0;
	//		if (clrFrame->lpVtbl->GetLocalVariableByIndex(clrFrame, args.varIdx, &locVar, 0, 0, 0) != S_OK)
	//			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "loc var get failed\n");
	//		clrFrame->lpVtbl->Release(clrFrame);
	//		WatchNode w;
	//		w.GetManagedType(locVar);

	//		sophis::FIELD_DESC basicField;
	//		basicField.TypeId = 0;
	//		print_field(basicField, w.module, w.address, false, &w.type);
	//		res = S_OK;
	//		goto evalTooltipFinish;
	//	}
	//	else
	//	{
	//		res = E_FAIL;
	//		goto evalTooltipFinish;
	//	}
	}

	//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "buf: %s\n", buf);
	g_ExtControl->Execute(DEBUG_OUTCTL_ALL_CLIENTS |
		DEBUG_OUTCTL_OVERRIDE_MASK |
		DEBUG_OUTCTL_NOT_LOGGED,
		buf, // Command to be executed
		DEBUG_EXECUTE_DEFAULT);
	//g_ExtSymbols->OutputTypedDataVirtual(DEBUG_OUTCTL_ALL_CLIENTS,
	//									 address, module, typeId, 0); // doesn't output type

evalTooltipFinish:
	sysObj->Release();
	return res;
}
