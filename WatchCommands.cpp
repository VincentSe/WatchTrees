/*++

Copyright (c) 2017  Vincent Semeria

--*/

// Commands defined in the CDB user interface, that manipulate watches :
// Add watch, remove watch, print watches...

#include "globals.h"
#include "watches.h"

#include <DbgHelp.h>

HRESULT CALLBACK
new_watch(PDEBUG_CLIENT4 Client, PCSTR args)
{
	Watch* w = new Watch();
	w->fValTree.offset = (unsigned long)gWatches.size();
	w->fExpr = args;
	gWatches.emplace_back(std::move(*w));
	return S_OK;
}

HRESULT CALLBACK
rename_watch(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	unsigned int offset;
	char watchName[128];
	const int numScan = sscanf(args, "%d %s", /*out*/&offset, /*out*/watchName);
	if (numScan != 2 || offset < 0 || offset >= gWatches.size())
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "!unknown watch to rename.\n");
		return E_FAIL;
	}

	Watch& w = gWatches[offset];
	w.fValTree.Prune();
	w.fValTree.typeId = 0;
	w.fValTree.address = 0;
	w.fExpr = watchName;

	return S_OK;
}

HRESULT CALLBACK
clear_watch(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	unsigned int watchIndex = -1;
	int r = sscanf(args, "%d", &watchIndex);
	if (r <= 0 || watchIndex < 0 || watchIndex >= gWatches.size())
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to remove: %d\n", watchIndex);
	}
	else
	{
		gWatches.erase(gWatches.begin() + watchIndex);
	}
	return S_OK;
}

HRESULT CALLBACK
clear_watches(PDEBUG_CLIENT Client, PCSTR args)
{
	UNREFERENCED_PARAMETER(Client);
	UNREFERENCED_PARAMETER(args);
	gWatches.clear();
	return S_OK;
}

HRESULT CALLBACK
expand_watch(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	char* pch = strtok((char*)args, " ");
	if (!pch)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to expand\n");
		return E_FAIL;
	}

	// Parse numbers separated by spaces
	unsigned int watchPos[64];
	int depth = 0;
	while (pch)
	{
		sscanf(pch, "%d", watchPos + depth);
		pch = strtok(0, " ");
		depth++;
	}

	if (watchPos[0] < 0 || watchPos[0] >= gWatches.size())
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to expand %d\n", watchPos[0]);
		return E_FAIL;
	}

	TypedValueTree* w = &gWatches[watchPos[0]].fValTree;
	if (depth >= 2)
		w = w->FindWatchPath(watchPos + 1, depth - 1);

	if (!w)
	{
		TypedValueTree* parent = gWatches[watchPos[0]].fValTree.FindWatchPath(watchPos + 1, depth - 2);
		if (parent)
		{
			w = parent->NewSubWatch(watchPos[depth - 1]);
			// w will be expanded below, it has no fieldCount yet
			if (!w)
			{
				return E_FAIL;
			}
		}
		else
		{
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Cannot find watch depth %d pos (", depth);
			for (int i = 0; i < depth; i++)
				g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "%d, ", watchPos[i]);
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "\n");
			return E_FAIL;
		}
	}

	w->FillFieldsAndChildren();
	return S_OK;
}

HRESULT CALLBACK
collapse_watch(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	char* pch = strtok((char*)args, " ");
	if (!pch)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to collapse\n");
		return E_FAIL;
	}

	// Parse numbers separated by spaces
	int depth = 0;
	unsigned int watchPos[64];
	while (pch)
	{
		sscanf(pch, "%d", /*out*/watchPos + depth);
		pch = strtok(NULL, " ");
		depth++;
	}

	if (watchPos[0] < 0 || watchPos[0] >= gWatches.size())
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to expand %d\n", watchPos[0]);
		return E_FAIL;
	}

	TypedValueTree* w = &gWatches[watchPos[0]].fValTree;
	if (depth >= 2)
		w = w->FindWatchPath(watchPos+1, depth-1);
	if (!w)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to collapse\n");
		return S_FALSE;
	}
	w->expanded = false;
	return S_OK;
}

HRESULT CALLBACK
print_watches(PDEBUG_CLIENT4 Client, PCSTR args)
{
	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	char* pch = strtok((char*)args, " ");
	bool reeval = pch && (strncmp(pch, "--reevalExpr", 2) == 0);

	g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "### WATCHES ###\n");
	std::vector<WatchLine> watchLines(1);
	watchLines[0].name = "  Name";
	watchLines[0].value = "Value";
	watchLines[0].type = "Type";
	for (Watch& w : gWatches)
	{
		HRESULT eval = w.fLastEval;
		if (reeval)
			eval = w.evaluate();
		if (eval == S_OK)
			w.Print(/*out*/watchLines);
		else
		{
			watchLines.resize(watchLines.size() + 1);
			watchLines.back().name = "  " + w.fExpr;
			watchLines.back().type = "### OUT OF SCOPE ###";
		}
	}

	size_t nameSize = 0;
	size_t valueSize = 0;
	for (const WatchLine& l : watchLines)
	{
		if (l.name.size() > nameSize) nameSize = l.name.size();
		if (l.value.size() > valueSize) valueSize = l.value.size();
	}

	for (WatchLine& l : watchLines)
	{
		l.name.resize(nameSize + 2, ' ');
		l.value.resize(valueSize + 2, ' ');
		std::string s = l.name + l.value + l.type;
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, s.c_str());
		if (l.cStrAddr)
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, " \"%ma\"\n", l.cStrAddr);
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "\n");
	}

	return S_OK;
}

HRESULT CALLBACK
set_watch_value(PDEBUG_CLIENT4 Client, PCSTR args)
{
	// for simple value types : bool, long, double, pointers

	NativeDbgEngAPIManager dbgApi(Client);
	if (!dbgApi.initialized) return E_FAIL;

	unsigned int watchPos[64];
	int depth = 0;
	char* pch = strtok((char*)args, " ");
	if (!pch)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to set\n");
		return E_FAIL;
	}

	while (pch && (sscanf(pch, "%d", watchPos + depth) == 1))
	{
		pch = strtok(NULL, " ");
		depth++;
	}
	//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "rest of string: %s\n", pch);
	if (pch && *pch == ':')
		pch++;
	else
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "usage:\nx y z :value\n");
		return E_FAIL;
	}

	TypedValueTree* w = gWatches[watchPos[0]].fValTree.FindWatchPath(watchPos + 1, depth - 1);
	TypedValueTree* parent = 0;
	ULONG64 TypeId = 0;
	ULONG64 Module = 0, Address = 0;
	char typeName[2048];
	if (w)
	{
		// set w itself
		strcpy_s(/*out*/typeName, 2048, w->type.c_str());
		TypeId = w->typeId;
		Module = w->module;
		Address = w->address;

	}
	else
	{
		parent = gWatches[watchPos[0]].fValTree.FindWatchPath(watchPos + 1, depth - 2);
		if (parent)
		{
			// set a field of parent, don't create subwatch
			ULONG offset = watchPos[depth - 1];
			Field fieldDesc;
			if (parent->GetField(offset, /*out*/fieldDesc) == S_OK)
			{
				TypeId = fieldDesc.TypeId;
				Module = fieldDesc.module;
				Address = fieldDesc.address;
				if (g_ExtSymbols->GetTypeName(Module, (ULONG)TypeId, /*out*/typeName, 2048, 0) != S_OK)
				{
					g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Couldn't get type name %d\n", TypeId);
					return E_FAIL;
				}
			}
			else
			{
				strcpy_s(typeName, 1024, parent->type.c_str());
				if (typeName[strlen(typeName) - 1] == '*')
				{
					// set pointed value
					Address = 0; // parent->dynamicDereference;
					typeName[strlen(typeName) - 1] = 0;
				}
			}
		}
		else
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown parent to set\n");
	}

	if (!Address)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Unknown watch to set %d\n", TypeId);
		return E_FAIL;
	}

	// PVOID val = 0;
	// ULONG size = 0;
	// long valI;
	// double valF;
	// bool valB;
	// if (strcmp(typeName, "int") == 0
	// 	|| strcmp(typeName, "long") == 0)
	// {
	// 	if (sscanf(pch, "%d", &valI) == 1)
	// 	{
	// 		val = &valI;
	// 		size = 4;
	// 	}
	// }
	// else if (strcmp(typeName, "double") == 0)
	// {
	// 	if (sscanf(pch, "%f", &valF) == 1)
	// 	{
	// 		val = &valF;
	// 		size = 8;
	// 	}
	// }
	// else if (strcmp(typeName, "bool") == 0)
	// {
	// 	if (strcmp(pch, "true") == 0)
	// 	{
	// 		valB = true;
	// 		val = &valB;
	// 		size = 1;
	// 	}
	// 	else if (strcmp(pch, "false") == 0)
	// 	{
	// 		valB = false;
	// 		val = &valB;
	// 		size = 1;
	// 	}
	// }

	// ULONG cb;
	// if (val && g_ExtSymbols->WriteTypedDataVirtual(Address,
	// 											   Module,
	// 											   TypeId,
	// 											   val,
	// 											   size,
	// 											   &cb) == S_OK
	//     && (cb == size))
	// {
	// 	if (w) w->Print();
	// 	else if (parent) parent->Print();
	// }
	// else
	// 	g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Watch set value failed\n");

	char cmd[256];
	sprintf_s(/*out*/cmd, 256, "?? *(%s*)0x%p =", typeName, (void*)Address);
	strcat_s(cmd, 256, pch);
	g_ExtControl->Execute(DEBUG_OUTCTL_IGNORE, // print the resulting watch instead
		cmd,
		0); // only simple types

	return S_OK;
}

struct SymEnumContext
{
	ULONG64 hProcess = 0;
};
