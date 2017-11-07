/*++

Copyright (c) 2017  Vincent Semeria

--*/


// watch container

#include "watches.h"
#include "globals.h"

#define KDEXT_64BIT 
// Structures that describe structures (fPointer, fStruct, fArray, ...)
#include "wdbgexts.h"

// PDB reading and searching functions
#include <DbgHelp.h>

#include <sstream>
#include <algorithm>

std::vector<Watch> gWatches;

TypedValueTree& TypedValueTree::operator=(TypedValueTree&& other)
{
	fieldName = std::move(other.fieldName);
	module = std::move(other.module);
	typeId = std::move(other.typeId);
	type = std::move(other.type);
	fPointer = std::move(other.fPointer);
	fStruct = std::move(other.fStruct);
	fArray = std::move(other.fArray);
	starCount = std::move(other.starCount);
	dereferences = std::move(other.dereferences);
	expanded = std::move(other.expanded);
	address = std::move(other.address);
	fields = std::move(other.fields);
	fieldCount = std::move(other.fieldCount);
	TypeSize = std::move(other.TypeSize);
	offset = std::move(other.offset);
	children = std::move(other.children);
	parent = std::move(other.parent);

	for (TypedValueTree& c : this->children)
		c.parent = this;
	return *this;
}

TypedValueTree::TypedValueTree(TypedValueTree&& other)
{
	*this = std::forward<TypedValueTree&&>(other);
}

Watch& Watch::operator=(Watch&& other)
{
	expr = std::move(other.expr);
	valTree = std::move(other.valTree);
	return *this;
}

Watch::Watch(Watch&& other)
{
	*this = std::forward<Watch&&>(other);
}


int countFinalStars(const char* type)
{
	// There could be stars in the template inner types, only count the final ones.

	int starCount = 0;
	for (const char* c = type + (strlen(type) - 1); c >= type; c--)
	{
		if (*c == '*')
		{
			starCount++;
		}
		else if (*c > ' ')
			break; // invalid character
	}
	return starCount;
}

std::vector<TypedValueTree>::iterator insert_subwatch(TypedValueTree&& w, TypedValueTree& where)
{
	w.parent = &where;
	auto child = where.children.begin();
	auto endChildren = where.children.end();
	while (child != endChildren && child->offset < w.offset)
		child++;

	return where.children.insert(child, std::forward<TypedValueTree&&>(w));
}

void TypedValueTree::Prune(std::vector<TypedValueTree>::iterator fromChild)
{
	children.erase(fromChild, children.end());
	fields.clear();
	if (!fArray)
		fieldCount = 0;
}

void TypedValueTree::Prune()
{
	Prune(children.begin());
}

//struct GetFieldRequest
//{
//	GetFieldRequest()
//	{
//		ZeroMemory(this, sizeof(GetFieldRequest));
//		baseData.Operation = EXT_TDOP_GET_FIELD;
//		baseData.InStrIndex = (ULONG64)fieldName - (ULONG64)this; // offset so that the request finds expr
//	}
//
//	void Reset()
//	{
//		ZeroMemory(this, sizeof(GetFieldRequest));
//		baseData.Operation = EXT_TDOP_GET_FIELD;
//		baseData.InStrIndex = (ULONG64)fieldName - (ULONG64)this;
//	}
//	
//	EXT_TYPED_DATA baseData;
//	char fieldName[256];
//};

bool TypedValueTree::TransformedType() const
{
	return this->fArray
		|| this->type.compare(0, 12, "std::vector<") == 0
		|| this->type.compare(0, 18, "stlpd_std::vector<") == 0
		|| this->type.compare(0, 9, "std::map<") == 0
		|| this->type.compare(0, 9, "std::set<") == 0
		|| this->type.compare(0, 10, "std::list<") == 0
		|| this->type.compare(0, 25, "std::_Tree_const_iterator") == 0
		|| this->type.compare(0, 19, "std::_Tree_iterator") == 0
		|| this->type.compare(0, 21, "std::_Vector_iterator") == 0
		|| this->type.compare(0, 27, "std::_Vector_const_iterator") == 0
		|| this->fieldName.compare(0, 7, "_Myhead") == 0;
}

//struct FieldContext
//{
//	std::vector<Field>* fields;
//	ULONG inTypeId;
//	ULONG64 module;
//	ULONG outFieldCount;
//};
//
//ULONG WDBGAPI fieldCallBack(FIELD_INFO* pField, PVOID UserContext)
//{
//	// pField->TypeId is a SymTagData, the symbol carrying the name of the field.
//	// The symbol of the type of pField is not directly here in pField. We can have it by 
//	// SymGetTypeInfo(pField->TypeId, TI_GET_TYPE).
//
//	// This method is not called back for fields coming from virtual derivations.
//
//	FieldContext* context = (FieldContext*)UserContext;
//
//	if (context->inTypeId == pField->TypeId)
//	{
//		return 0; // can happen when get_type_info is called with a field typeId,
//				  // just skip this repeated field
//	}
//
//	context->fields->resize(context->fields->size() + 1);
//	Field& outField = context->fields->back();
//	strcpy_s(outField.fName, 128, (char*)pField->fName);
//	outField.size = pField->size;
//	outField.TypeId = pField->TypeId;
//	outField.address = pField->address;
//	//outField.FieldOffset = pField->FieldOffset; // 0, 1, 2, ... looks not filled
//	outField.fPointer = (bool)pField->fPointer;
//	outField.fArray = (bool)pField->fArray;
//	outField.fStruct = (bool)pField->fStruct;
//	//outField.fConstant = pField->fConstant;
//	outField.fStatic = pField->fStatic;
//	context->fields->back().module = context->module;
//	context->outFieldCount++;
//	return 0;
//}

void sym_get_type_info(ULONG64 Module,
						ULONG TypeId,
						/*out*/ std::vector<Field>& fields,
						ULONG offset)
{
	fields.clear();
	ULONG64 hProcess = 0;
	g_ExtSystem->GetCurrentProcessHandle(/*out*/&hProcess);
	DWORD childrenCount = 0;

	DWORD symtag = 0;
	BOOL b = SymGetTypeInfo((HANDLE)hProcess, Module, TypeId, TI_GET_SYMTAG, /*out*/&symtag);
	if (symtag == 14)
	{
		// Pointer types like Foo* have no children, replace them by their pointed type.
		b = SymGetTypeInfo((HANDLE)hProcess, Module, TypeId, TI_GET_TYPE, /*out*/&TypeId);
	}

	// Fields and methods of TypeId. 
	b = SymGetTypeInfo((HANDLE)hProcess, Module, TypeId, TI_GET_CHILDRENCOUNT, &childrenCount);
	if (!b)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Failed to get children of type %d\n", TypeId);
		return;
	}

	std::vector<ULONG> ids(childrenCount + 2);
	ids[0] = childrenCount; // child count
	ids[1] = 0; // start child
	b = SymGetTypeInfo((HANDLE)hProcess, Module, TypeId, TI_FINDCHILDREN, &ids.front());

	WCHAR* symName = 0;
	for (int i = 2; i < ids.size(); i++)
	{
		b = SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_SYMTAG, /*out*/&symtag);

		DWORD addr = 0;

		if (symtag == 18 // base class
			|| symtag == 7) // data
		{
			const bool addressFound = SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_OFFSET, /*out*/&addr);
			ULONG virtualSuperClassIndex = -1;
			if (symtag == 7)
			{
				// Find which kind of data this field is
				if (!addressFound)
					continue; // skip static fields
				ULONG fieldType = 0;
				SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_TYPE, /*out*/&fieldType);
				SymGetTypeInfo((HANDLE)hProcess, Module, fieldType, TI_GET_SYMTAG, /*out*/&symtag);
			}
			else if (symtag == 18)
			{
				if (addressFound) // Recursively fill the super class's fields
				{
					SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_TYPE, /*out*/&TypeId);
					sym_get_type_info(Module, TypeId, /*out*/ fields, addr);
					continue;
				}
				else // Display the virtual super class as a struct field, so that TypedValueTree::Print resolves the vbtable
					b = SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_VIRTUALBASEDISPINDEX, /*out*/&virtualSuperClassIndex);

			}
			fields.resize(fields.size() + 1);
			Field& field = fields.back();
			if (SymGetTypeInfo((HANDLE)hProcess, Module, ids[i], TI_GET_SYMNAME, /*out*/&symName))
			{
				std::wcstombs(/*out*/field.fName, symName, 128);
				LocalFree(symName); symName = 0;
			}

			field.TypeId = ids[i];
			field.address = addr;
			field.module = Module;
			field.virtualSuperClassIndex = virtualSuperClassIndex;

			switch (symtag)
			{
			case 11:
			case 18: // display fields of the base class instead ?
				field.fStruct = true;
				break;
			case 14:
				field.fPointer = true;
				break;
			case 15:
				field.fArray = true;
				break;
			}
		}
	}
}

HRESULT TypedValueTree::GetField(unsigned long fieldOffset,	/*out*/Field& fieldDesc) const
{
	if (!this->typeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Get field: zero type Id\n");
		return E_FAIL;
	}
	
	fieldDesc = this->fields[fieldOffset];

	// Convert SymTagData into a type symbol (SymTagUDT or SymTagPointerType or ...)
	DWORD symType = 0;
	ULONG64 hProcess = 0;
	g_ExtSystem->GetCurrentProcessHandle(/*out*/&hProcess);
	if (!SymGetTypeInfo((HANDLE)hProcess, fieldDesc.module, fieldDesc.TypeId, TI_GET_TYPE, /*out*/&symType))
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "GetField, couldn't get type info\n");
		return E_FAIL;
	}
	fieldDesc.TypeId = symType;
	fieldDesc.address += GetAddressOfData();
	return S_OK;
}

bool find_watch_position(const TypedValueTree& w, const TypedValueTree& where, /*out*/int* ptr, /*out*/unsigned int* count)
{
	if (*count >= 16)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Max watch depth is 16\n");
		return 0;
	}
	
	if (&w == &where)
		return true;

	int saveCount = *count;
	bool found = false;
	auto child = where.children.begin();
	while (!found && child != where.children.end())
	{
		ptr[saveCount] = child->offset;
		*count = saveCount + 1;
		found = find_watch_position(w, *child, ptr, count);
		child++;
	}
	return found;
}

enum eBasicType
{
	eShort, eDouble,
	eLong, eULong,
	eInt, eUInt,
	eBool, eNone
};

// For watches that are pointers to basic types, we only have the type size through the type name.
// But even knowing the size, type double is special, it has to do *(double*)&fieldData.
std::string print_basic_value(	ULONG64 addr,
								ULONG64 typeId,
								ULONG64 Module,
								const char* type,
								long typeSize)
{
	std::string res;
	ULONG cb;
	eBasicType bType = eNone;
	if (strncmp(type, "long", 4) == 0)
		bType = eLong;
	else if (strncmp(type, "unsigned long", 13) == 0)
		bType = eULong;
	else if (strncmp(type, "int", 3) == 0
		|| strncmp(type, "System.Int32", 12) == 0)
		bType = eInt;
	else if (strncmp(type, "unsigned int", 12) == 0)
		bType = eUInt;
	else if (strncmp(type, "double", 6) == 0)
		bType = eDouble;
	else if (strncmp(type, "short", 5) == 0)
		bType = eShort;
	else if (strncmp(type, "bool", 4) == 0)
		bType = eBool;

	if (bType == eNone)
	{
		// GetConstantName returns S_OK too often, keep it at the very last !
		ULONG64 fieldData = 0; // 8 bytes
		char enumValue[256] = "";
		if (typeSize <= 8)
			ReadMemory(addr, &fieldData, typeSize ? typeSize : 4, &cb); // enums seem to take 4 bytes
		if (typeId && g_ExtSymbols->GetConstantName(Module, (ULONG)typeId, fieldData, /*out*/enumValue, 256, &cb) == S_OK)
		{
			res += std::to_string(fieldData) + " ( " + enumValue + " )";
		}
		return res;
	}

	if (typeSize == 0)
	{
		switch (bType)
		{
		case eBool: typeSize = 1; break;
		case eShort: typeSize = 2; break;
		case eInt:
		case eUInt:
		case eLong: typeSize = 4; break;
		case eDouble: typeSize = 8; break;
		}
	}

	ULONG64 fieldData = 0; // 8 bytes
	if (typeSize <= 8)
		ReadMemory(addr, &fieldData, typeSize, &cb);

	switch (bType)
	{
	case eBool:
		res = fieldData ? "true" : "false";
		break;
	case eShort:
		res = std::to_string((short)fieldData);
		break;
	case eLong:
	case eULong:
	case eInt:
	case eUInt:
		res = std::to_string((long)fieldData);
		break;
	case eDouble:
		res = std::to_string(*(double*)&fieldData);
		break;
	}

	return res;
}

WatchLine print_field(const Field& field,
						 ULONG64 Module,
						 ULONG64 addr,
						 long indent)
{
	WatchLine res;

	res.name.resize(indent + 2, ' ');
	if (false) // field.fStatic
	{
		res.name += "STATIC ";
		res.name += field.fName; // must print it to keep field indexes valid
		return res;
	}

	if (field.fStruct || field.fPointer || field.fArray)
		res.name[indent] = '+'; // If expanded, this field is replaced by a subwatch and not printed here anymore
	res.name += field.fName;

	ULONG cb;
	char fieldTypeBuf[2048] = "";
	const char* fieldType;
	if (g_ExtSymbols->GetTypeName(Module, (ULONG)field.TypeId, /*out*/fieldTypeBuf, 2048, &cb) == S_OK)
		fieldType = (char*)fieldTypeBuf;
	else
	{
		res.type = "### ERROR ###";
		return res;
	}
	
	ULONG64 fieldData = 0; // 8 bytes
	std::stringstream ss;
	if (field.fPointer)
	{
		// pointer field inside a struct or class, just print its pointed address
		const int ptrSize = sizeof(long*);
		ReadMemory(addr + field.address, &fieldData, ptrSize, &cb);
		ss << "0x" << std::hex << fieldData;
		res.value = ss.str();
	}
	else if (field.fArray)
	{
		// an array field is completely stored inside the object, unlike a pointer field which only stores an address in the object
		if (strcmp(fieldType, "char[]") == 0)
			res.cStrAddr = addr + field.address;
		ss << "0x" << std::hex << (addr + field.address);
		res.value = ss.str();
	}
	else if (!field.fStruct)
	{
		// basic types
		res.value = print_basic_value(addr + field.address, field.TypeId, Module, fieldType, field.size);
	}

	res.type = fieldType;
	if (strncmp(fieldType, "char*", 5) == 0)
		res.cStrAddr = fieldData;
	return res;
}

void TypedValueTree::FillFields()
{
	this->fields.clear();

	if (fArray || !this->module)
		return;

	sym_get_type_info(this->module, this->typeId, /*out*/this->fields, 0);
	this->fieldCount = this->fields.size();
	return;

	// Auto-dereferences pointer types, but not virtual inheritance.
	// Doesn't handle virtual fields.
	// g_ExtSymbols->OutputTypedDataVirtual is too slow, because it resolves virtual inheritance for all base classes.

	//FieldContext context;
	//context.outFieldCount = 0;
	//context.fields = &this->fields;
	//context.module = this->module;

	//static SYM_DUMP_PARAM typeInfo =
	//{
	//	sizeof(SYM_DUMP_PARAM), // .size =
	//	0, // sName
	//	DBG_DUMP_CALL_FOR_EACH | DBG_DUMP_NO_PRINT, // .Options =
	//	0, // .addr = null address, means print type info only, without reference to base classes
	//	NULL, // .listLink = 
	//	0, // .pBuffer =  context or buffer
	//	fieldCallBack, // .CallbackRoutine = function called on each field
	//	0, //.nFields =
	//	NULL //.Fields = means get all fields
	//};

	//// Seems typeName is stronger than TypeId in IG_DUMP_SYMBOL_INFO : 
	//// if it is given it will not use TypeId
	//typeInfo.sName = 0;
	//typeInfo.ModBase = this->module;
	//typeInfo.TypeId = this->typeId;
	//context.inTypeId = typeInfo.TypeId;
	//typeInfo.fPointer = 0;
	//typeInfo.fStruct = 0;
	//typeInfo.Context = (void*)&context;

	//// Through dbgeng.dll, will make dozens of calls to dbghelp.dll!SymGetTypeInfo
	//ULONG res = Ioctl(IG_DUMP_SYMBOL_INFO, /*out*/&typeInfo, typeInfo.size);

	//this->fieldCount = fields.size();
	// for watches on references, typeId will be undefined and previous call will fail
}

void TypedValueTree::CopyTypeInfo(const TypedValueTree& other)
{
	this->fields = other.fields;
	this->fieldCount = other.fieldCount;
	this->type = other.type;
	this->typeId = other.typeId;
	this->module = other.module;
	this->fPointer = other.fPointer;
	this->fStruct = other.fStruct;
	this->fArray = other.fArray;
	this->starCount = other.starCount;
	this->dereferences = other.dereferences;
}

ULONG64 expand_string(const TypedValueTree* w)
{
	// Return the address of the underlying char*. Only works when the union _Bx is interpreted as such a char* (strings longer than 4 characters ?).
	const Field& bx = w->FindField("_Bx");
	if (!bx.TypeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "_Bx not found\n");
		return E_FAIL;
	}

	ULONG64 cAddr = 0;
	ULONG cb;
	const int ptrSize = sizeof(long*);
	ReadMemory(w->GetAddressOfData() + bx.address, /*out*/&cAddr, ptrSize, &cb);
	return cAddr;
}

void Watch::Print(std::vector<WatchLine>& output)
{
	output.resize(output.size() + 1);
	std::string& name = output.back().name;
	name = "  ";
	name[0] = valTree.GetExpandCharacter();
	name += expr;
	valTree.Print(0, output);
}

std::string TypedValueTree::GetDeepType(unsigned __int64 addr) const
{
	// Use virtual table to know the subtype
	const int ptrSize = sizeof(long*);
	ULONG cb;
	CHAR vTableName[256] = "";
	ULONG64 addr2 = 0;
	ULONG64 displ;
	bool accessViol = false;
	if (!ReadMemory(addr, &addr2, ptrSize, &cb) || cb != ptrSize)
	{
		// Memory access violation (null or uninitialized pointer for instance)
		accessViol = true;
	}
	bool vTable = false; // TODO don't make this query for basic pointers double*, long*, ...
	if (!accessViol && this->fPointer &&
		g_ExtSymbols->GetNameByOffset(addr2,
			/*out*/vTableName,
			256,
			&cb,
			&displ) == S_OK)
	{
		if (strcmp(vTableName + (strlen(vTableName) - 11), "::`vftable'") == 0
			|| strcmp(vTableName + (strlen(vTableName) - 17), "::`local vftable'") == 0
			|| strcmp(vTableName + (strlen(vTableName) - 11), "::`vbtable'") == 0) // todo virtual inheritance
		{
			return vTableName;
		}
	}
	return "";
}

char TypedValueTree::GetExpandCharacter() const
{
	const bool canBeExpanded =
		((this->fPointer || this->fArray) && this->starCount > this->dereferences)
		|| this->fStruct
		|| (fieldCount > 0 && this->starCount == this->dereferences);
	if (canBeExpanded)
		return this->expanded ? '-' : '+';
	else
		return ' ';
}

void TypedValueTree::Print(long indent, std::vector<WatchLine>& output)
{
	if (!fieldName.empty()) // Top-level watches already printed their expressions
	{
		output.resize(output.size() + 1);
		output.back().name.resize(indent + 2, ' ');
		output.back().name[indent] = GetExpandCharacter();
		output.back().name += fieldName;
	}

	// Print root value
	const ULONG64 addr = GetAddressOfData();
	if (this->typeId && this->module && this->address)
	{			
		if ((this->fPointer || this->fArray) && this->starCount > this->dereferences)
		{
			// Print the pointed memory address
			std::stringstream ss;
			ss << "0x" << std::hex << addr;
			output.back().value = ss.str();
			// Continue below to print the pointed fields or pointed basic value on the next lines (if the pointer is expanded)
		}
		else if (addr && fieldCount==0 && !this->fStruct)
			output.back().value = print_basic_value(addr, this->typeId, this->module, this->type.c_str(), this->TypeSize);
	}

	// Print type (or string value) and end of line
	if (this->type.compare(0, 18, "std::basic_string<") == 0)
		output.back().cStrAddr = expand_string(this);
	if (this->type == "char[]" || this->type == "char*")
		output.back().cStrAddr = addr;
	else
	{
		const std::string deepType = GetDeepType(addr);
		output.back().type = this->type;
		if (deepType != "")
			output.back().type += " (" + deepType + ")";
	}

	if (!this->expanded)
		return;

	// Recursively print fields, pointed basic values and subwatches
	if (this->fPointer && addr && fieldCount == 0 && this->children.empty())
	{
		// Pointed basic value, print it without name and type
		output.resize(output.size() + 1);
		output.back().value = print_basic_value(addr, this->typeId, this->module, this->type.c_str(), 0);
	}
	else
	{
		// Print children and fields, children having a higher priority than fields
		auto notYetPrintedChild = this->children.begin();
		if ((this->starCount == this->dereferences || this->starCount == this->dereferences + 1)
			&& !TransformedType() && addr)
			for (ULONG i = 0; i < fieldCount; i++)
			{
				// Either print the i-th field or its subwatch
				auto child = notYetPrintedChild;
				while (child != this->children.end())
				{
					if (child->offset == i) break;
					child++;
				}
				if (child != this->children.end())
				{
					// addr may have been modified because this watch is a pointer, or higher up in the call stack
					if (fields[i].virtualSuperClassIndex == -1)
						child->address = addr + fields[i].address;
					else
					{
						ULONG64 vbtableAddr = 0; // write 64 bits
						ULONG cb;
						const int ptrSize = sizeof(long*);
						ReadMemory(this->address, /*out*/&vbtableAddr, ptrSize, &cb);
						child->address = 0;
						ReadMemory(vbtableAddr + 4*fields[i].virtualSuperClassIndex, /*out*/&child->address, 4, &cb);
						child->address += addr;
					}
					child->Print(indent + 2, output);
					notYetPrintedChild = child+1;
				}
				else
					output.push_back(print_field(fields[i], this->module, addr, indent + 2));
			}

		// Finish printing children
		while (notYetPrintedChild != this->children.end())
		{
			notYetPrintedChild->Print(indent + 2, output); // TODO update child's address
			notYetPrintedChild++;
		}
	}
}

ULONG64 TypedValueTree::GetAddressOfData() const
{
	ULONG64 addr = this->address;
	if (this->starCount > this->dereferences && this->fPointer) // dereference pointer
	{
		addr = 0; // write 64 bits
		ULONG cb;
		const int ptrSize = sizeof(long*);
		ReadMemory(this->address, /*out*/&addr, ptrSize, &cb);
	}
	return addr;
}

TypedValueTree* TypedValueTree::FindWatchPath(const unsigned int* watchPos, int depth)
{
	if (depth == 0)
		return this;

	const int firstIndex = watchPos[0];
	auto w = std::find_if(children.begin(), children.end(),
		[firstIndex](const TypedValueTree& c) { return c.offset >= firstIndex; }); // optimization because children offsets are sorted, we really search for ==
	return (w == children.end() || w->offset != firstIndex)
		? 0 // not found
		: w->FindWatchPath(watchPos+1, depth-1);
}

struct slv_args
{
	ULONG varIdx;
	const char* varName;
	bool varFound;
};

bool selectLocVar(const char* varName, void* _args)
{
	slv_args* args = (slv_args*)_args;
	//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "select loc var %s\n", varName);

	if (strncmp(varName, "CS$", 3) == 0)
	{
		return true; // skip compiler-generated variables
	}
	
	if (strcmp(varName, args->varName) == 0)
	{
		args->varFound = true;		
		return false;
	}
	else
	{
		args->varIdx++;
		return true;
	}
}

unsigned int cut_array_query(char* s);

struct EvaluateRequest
{
	EvaluateRequest()
	{
		ZeroMemory(this, sizeof(EvaluateRequest));
		baseData.Operation = EXT_TDOP_SET_FROM_EXPR; // EXT_TDOP_EVALUATE;
		baseData.InStrIndex = (ULONG64)expr - (ULONG64)this; // offset so that the request finds expr
	}
	void Reset()
	{
		ZeroMemory(this, sizeof(EvaluateRequest));
		baseData.Operation = EXT_TDOP_SET_FROM_EXPR; // EXT_TDOP_EVALUATE;
		baseData.InStrIndex = (ULONG64)expr - (ULONG64)this; // offset so that the request finds expr		
	}

	EXT_TYPED_DATA baseData;
	char expr[256]; // the expression to evaluate
};


HRESULT evaluateExpr(const char* expr,
	/*out*/ PSYM_DUMP_PARAM p,
	/*out*/ PULONG64 dynamicDereference)
{
	ZeroMemory(p, sizeof(SYM_DUMP_PARAM));
	int arrayQuery = cut_array_query(const_cast<char*>(expr));

	EvaluateRequest req;
	if (arrayQuery)
	{
		sprintf_s(req.expr, 256, "@@c++(*%s)", expr); // to get the pointed type
	}
	else if (strncmp(expr, "@@c++(", 6) == 0) // force evaluation in C++ rather than assembler
		*(char**)&req.expr = (char*)expr;
	else
	{
		if (*expr == '*')
			sprintf_s(req.expr, 256, "@@c++(%s)", expr); // cannot insert $! before *
		else if (*expr == '&')
		{
			// A reference to a variable is a pointer type that may not be in the source code being debugged.
			// TODO remove the '&' and use the address as the value.
			sprintf_s(req.expr, 256, "@@c++(&$!%s)", expr + 1);
		}
		else
			sprintf_s(req.expr, 256, "@@c++($!%s)", expr);
	}

	HRESULT evalRes = g_ExtAdvanced->Request(DEBUG_REQUEST_EXT_TYPED_DATA_ANSI,
		&req, sizeof(EvaluateRequest),
		&req, sizeof(EvaluateRequest),
		NULL);
	if (evalRes != S_OK)
	{
		if (req.expr[8] == '(')
		{
			// maybe a cast, try without local module
			// TODO ADD A STAR BEFORE CAST EXPRESSION TO A POINTER, TO FORCE THE TYPE

			//req.Reset();
			char* c;
			for (c = req.expr + 8; *c; c++)
				c[-2] = *c;
			c[-2] = 0;
			//sprintf_s(req.expr, 256, "@@c++(%s)", expr);
			//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Array query: %s\n", req.expr);
			if (g_ExtAdvanced->Request(DEBUG_REQUEST_EXT_TYPED_DATA_ANSI,
				&req, sizeof(EvaluateRequest),
				&req, sizeof(EvaluateRequest),
				NULL) != S_OK)
			{
				g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Failed to evaluate expression %s\n", expr);
				return E_FAIL; // data est le pointeur, obtenir le type plus tard				
			}
		}
		else
			return E_FAIL;
	}

	p->ModBase = req.baseData.OutData.ModBase;
	p->TypeId = req.baseData.OutData.TypeId;
	p->addr = req.baseData.OutData.Offset;
	p->TypeSize = req.baseData.OutData.Size;
	*dynamicDereference = req.baseData.OutData.Data; // for virtual inheritance
	p->fStruct = (req.baseData.OutData.Tag == 11);
	p->fPointer = (req.baseData.OutData.Tag == 14); // SymTagEnum::SymTagPointerType (dbghelp.h)
	p->fArray = (req.baseData.OutData.Tag == 15); // SymTagEnum::SymTagArrayType

	if (arrayQuery) // TODO: handle both array queries and native arrays, maybe distinguish with fPointer
	{
		p->fPointer = false;
		p->fArray = true;
		p->nFields = arrayQuery; // arrays of double for now
		*dynamicDereference = p->addr;
	}
	else if (p->fArray)
		p->fPointer = true;

	return S_OK;
}

HRESULT Watch::evaluate()
{
	SYM_DUMP_PARAM p;
	ULONG64 dynDeref;
	if (evaluateExpr(expr.c_str(), &p, &dynDeref) != S_OK)
		return E_FAIL;

	valTree.address = p.addr;
	valTree.fArray = p.fArray;
	valTree.fPointer = (bool)p.fPointer;
	valTree.fStruct = p.fStruct;
	valTree.TypeSize = p.TypeSize;
	if (valTree.typeId != p.TypeId)
	{
		// new watch or type change
		valTree.Prune();
		valTree.module = p.ModBase;
		valTree.typeId = p.TypeId;
		ULONG cb;
		char type[2048];
		g_ExtSymbols->GetTypeName(valTree.module, (ULONG)valTree.typeId, /*out*/type, 2048, &cb);
		valTree.type = type;

		valTree.FillFields();

		if (valTree.fArray && !valTree.fPointer)
		{
			valTree.fieldCount = p.nFields;
			valTree.starCount = 1;
			valTree.type += "[]";
		}
		else
			valTree.starCount = countFinalStars(valTree.type.c_str());
		valTree.expanded = !valTree.TransformedType() && valTree.starCount<=1;
	}

	valTree.dereferences = 0;
	return S_OK;
}

unsigned int cut_array_query(char* s)
{
	// match ,[number] at end of s
	size_t n = strlen(s);
	int arrayQuery = 0;
	for (char* c = s + n; c > s; c--)
	{
		if (*c == ',')
		{
			*c = 0;
			sscanf(c+1, "%d", &arrayQuery);
			break;
		}
	}
	return arrayQuery;
}

HRESULT expand_array(/*out*/TypedValueTree* w)
{
	ULONG arraySize = 0;
	size_t arrayLen = w->fieldCount;

	w->Prune();
	w->fieldCount = arrayLen;

	EXT_TYPED_DATA ExtData;
	ZeroMemory(&ExtData, sizeof(ExtData));
	ULONG64 firstElemAddr = 0; // w->dynamicDereference;
	ULONG cb;
	char type[2048];
	std::string pointType = w->type;
	pointType.resize(pointType.size()-2);
		
	if (w->address && w->fPointer) // native arrays, not queries with ,number
	{
		ExtData.Operation = EXT_TDOP_SET_FROM_TYPE_ID_AND_U64;
		ExtData.InData.ModBase = w->module;
		ExtData.InData.TypeId = (ULONG)w->typeId; // doesn't work with field type IDs
		ExtData.InData.Offset = w->address; // Address, test
		HRESULT Status = g_ExtAdvanced->
			Request(DEBUG_REQUEST_EXT_TYPED_DATA_ANSI,
					&ExtData, sizeof(ExtData),
					&ExtData, sizeof(ExtData),
					NULL);
		if (Status != S_OK)
		{
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Cannot evaluate array's address\n");
			return E_FAIL;
		}
		arraySize = ExtData.OutData.Size;
		firstElemAddr = ExtData.OutData.Data;

		ExtData.InData = ExtData.OutData;
		ExtData.Operation = EXT_TDOP_GET_DEREFERENCE;
		if (g_ExtAdvanced->Request(DEBUG_REQUEST_EXT_TYPED_DATA_ANSI,
							   &ExtData, sizeof(EXT_TYPED_DATA),
							   &ExtData, sizeof(EXT_TYPED_DATA),
							   NULL) != S_OK)
		{
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "array dereference request failed %d\n", Status);
			return E_FAIL;
		}

		if (!arrayLen)
		{
			if (arraySize % ExtData.OutData.Size)
			{
				g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "corrupted array, element size %d, ", ExtData.OutData.Size);
				g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "array size %d\n", arraySize);
				return E_FAIL;
			}
			arrayLen = arraySize / ExtData.OutData.Size;
		}

		g_ExtSymbols->GetTypeName(ExtData.OutData.ModBase, ExtData.OutData.TypeId, /*out*/type, 2048, &cb);
		pointType = type;
		w->TypeSize = ExtData.OutData.Size;
	}

	unsigned int nbIter = 0;
	while (nbIter<arrayLen && nbIter<300)
	{
		// add subwatches
		TypedValueTree* sub = new TypedValueTree();
		sub->fieldName = std::string("[") + std::to_string(nbIter) + "]";
		sub->typeId = w->typeId; //ExtData.OutData.TypeId;
		sub->type = pointType;
		sub->module = w->module;
		sub->address = w->address + nbIter*w->TypeSize;
		sub->FillFields();
		sub->offset = nbIter;
		sub->starCount = 0; //starCount;
		sub->dereferences = 0;
		insert_subwatch(std::move(*sub), *w);

		nbIter++;
	}
	
	return S_OK;
}

HRESULT expand_iterator(/*out*/TypedValueTree* w, bool myVal)
{
	TypedValueTree ptr;
	ptr.FromField(w->FindField("_Ptr"), w->GetAddressOfData());
	if (!ptr.typeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "_Ptr not found\n");
		return E_FAIL;
	}

	ptr.FillFields();
	const Field& myValField = ptr.FindField("_Myval"); 
	if (!myValField.TypeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "_Myval not found\n");
		return E_FAIL;
	}
	
	auto sub = w->children.begin(); // TODO delete other children
	if (sub == w->children.end())
	{
		insert_subwatch(std::move(*new TypedValueTree()), *w);
		sub = w->children.begin();
	}
	sub->FromField(myValField, ptr.GetAddressOfData());

	char iterType[2048];
	g_ExtSymbols->GetTypeName(sub->module, sub->typeId, /*out*/iterType, 2048, 0);

	sub->fieldName = myVal ? "_Myval" : "_Ptr";
	sub->type = iterType;
	sub->FillFields();
	sub->offset = 0;
	sub->starCount = myVal ? 0 : 1;
	sub->dereferences = 0;

	return S_OK;
}

Field TypedValueTree::FindField(const char* fieldName) const
{
	const size_t fieldLen = strlen(fieldName);
	std::vector<Field>::const_iterator it =
		std::find_if(this->fields.begin(), this->fields.end(), [&](const Field& f)
			{ return strncmp(f.fName, fieldName, fieldLen) == 0; });
	return it == this->fields.end() ? Field() : *it;
}

void FindVectorFirst(const TypedValueTree& vec, /*out*/TypedValueTree& myFirst)
{
	const Field& myPair = vec.FindField("_Mypair");
	if (myPair.TypeId)
	{
		myFirst.FromField(myPair, vec.GetAddressOfData());
		myFirst.FillFields();
		const Field& myVal2 = myFirst.FindField("_Myval2");
		myFirst.FromField(myVal2, myFirst.GetAddressOfData());
		myFirst.FillFields();
		myFirst.FromField(myFirst.FindField("_Myfirst"), myFirst.GetAddressOfData());;
	}
	else
		myFirst.FromField(vec.FindField("_Myfirst"), vec.GetAddressOfData());
}

HRESULT expand_vector(/*out*/TypedValueTree& w)
{
	TypedValueTree myFirst;
	FindVectorFirst(w, /*out*/myFirst);
	if (!myFirst.typeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "get field _Myfirst failed\n");
		return E_FAIL;
	}

	ULONG64 hProcess = 0;
	g_ExtSystem->GetCurrentProcessHandle(/*out*/&hProcess);
	BOOL b;
	DWORD type = 0, baseType = 0;
	b = SymGetTypeInfo((HANDLE)hProcess, w.module, myFirst.typeId, TI_GET_TYPE, &type); // SymTagData -> SymTagPointerType
	if (!b || !SymGetTypeInfo((HANDLE)hProcess, w.module, type, TI_GET_TYPE, &baseType) // SymTagPointerType -> pointed type
		|| myFirst.typeId == type || baseType == type)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Cannot get pointed type\n");
		return E_FAIL;
	}

	ULONG cb;
	char pointType[1024];
	g_ExtSymbols->GetTypeName(w.module, baseType, /*out*/pointType, 1024, &cb);

	// Read first and last element pointers
	const int ptrSize = sizeof(long*);
	const ULONG64 first = myFirst.GetAddressOfData();
	ULONG64 last = 0;
	if (!ReadMemory(myFirst.address + ptrSize, &last, ptrSize, &cb))
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Couldn't read first and last elements.\n");
		return E_FAIL;
	}

	ULONG64 elemSize = 0;
	SymGetTypeInfo((HANDLE)hProcess, w.module, baseType, TI_GET_LENGTH, &elemSize);

	DWORD pointedTypeTag = 0;
	SymGetTypeInfo((HANDLE)hProcess, w.module, baseType, TI_GET_SYMTAG, &pointedTypeTag);
	if ( (last-first) % elemSize )
	{
		//g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "padding detected %d %d\n", first, last);
		//if ( ((last-first) % (elemSize+4)) == 0 )
		//	elemSize += 4;
		//else
		//{
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "corrupted vector, element size %d, ", elemSize);
			g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "first 0x%p\n", first);
			return E_FAIL;
		//}	
	}

	TypedValueTree itemTemplate;
	itemTemplate.type = pointType;
	itemTemplate.typeId = baseType;
	itemTemplate.module = w.module;
	itemTemplate.FillFields(); // slow, only do it for the template
	itemTemplate.starCount = 0;
	switch (pointedTypeTag)
	{
	case 11:
		itemTemplate.fStruct = true;
		break;
	case 14: // SymTagEnum::SymTagPointerType
		itemTemplate.fPointer = true;
		itemTemplate.starCount = 1;
		break;
	case 15:
		itemTemplate.fArray = true;
		break;
	}

	unsigned int nbIter = 0;
	w.children.resize(min(200, (last - first) / elemSize));
	for (TypedValueTree& child : w.children)
	{
		child.offset = nbIter;
		child.parent = &w;
		child.fieldName = "[" + std::to_string(nbIter) + "]";
		child.CopyTypeInfo(itemTemplate);
		child.address = first + nbIter*elemSize;
		nbIter++;
	}	
	return S_OK;
}

void TypedValueTree::FromField(const Field& field, ULONG64 addr)
{
	Prune();
	this->address = addr + field.address;
	this->typeId = field.TypeId;
	this->module = field.module;
	this->fStruct = field.fStruct;
	this->fArray = field.fArray;
	this->fPointer = field.fPointer;
	this->starCount = this->fPointer ? 1 : 0;
}

Field FindMapHead(TypedValueTree& map, bool myHead,
						/*out*/ ULONG64& myHeadAddress)
{
	if (myHead)
	{
		myHeadAddress = map.GetAddressOfData();
		return map.FindField("_Myval");
	}

	TypedValueTree v;
	Field f = map.FindField("_Mypair");
	if (f.TypeId)
	{
		v.FromField(f, map.GetAddressOfData());
		v.FillFields();
		f = v.FindField("_Myval2");
		v.FromField(f, v.GetAddressOfData());
		v.FillFields();
		f = v.FindField("_Myval2");
		v.FromField(f, v.GetAddressOfData());
		v.FillFields();
		f = v.FindField("_Myhead");
		v.FromField(f, v.GetAddressOfData());
	}
	else
		v.FromField(map.FindField("_Myhead"), map.GetAddressOfData());

	myHeadAddress = v.GetAddressOfData();
	v.FillFields();
	return v.FindField("_Myval");
	// 	if (myHeadWatch.fields.empty())
	//myHeadWatch.FillFields();
}

HRESULT expand_map(/*out*/TypedValueTree& w, bool myHead)
{
	ULONG64 myHeadAddress = 0;
	const Field& myVal = FindMapHead(w, myHead, /*out*/myHeadAddress);
	if (!myVal.TypeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "_Myval not found\n");
		return S_FALSE;	
	}

	char pairName[256];
	ULONG cb;
	g_ExtSymbols->GetTypeName(myVal.module, myVal.TypeId, /*out*/pairName, 256, &cb);
	
	// Read least element of map
	ULONG64 mapNode = 0;
	const int ptrSize = sizeof(long*);
	ReadMemory(myHeadAddress, &mapNode, ptrSize, &cb);

	if (myHeadAddress == mapNode)
		return S_OK; // empty map

	TypedValueTree pairTemplate;
	pairTemplate.typeId = myVal.TypeId;
	pairTemplate.module = myVal.module;
	pairTemplate.type = pairName;
	pairTemplate.starCount = 0; // it's the pair itself, not a pointer to it
	pairTemplate.fStruct = true;
	pairTemplate.FillFields();

	char iterState = 'd'; // down
	unsigned int nbIter = 0, nbIterGuard = 0;
	ULONG64 leftNode, rightNode, parentNode;
	auto child = w.children.begin();
	TypedValueTree* sub;
	while (nbIterGuard < 200)
	{
		if (iterState == 'd')
		{
			leftNode = 0;
			ReadMemory(mapNode, &leftNode, ptrSize, &cb);
			if (leftNode == myHeadAddress) // leaf
			{
				if (child == w.children.end())
				{
					sub = new TypedValueTree();
					sub->offset = nbIter;
					child = insert_subwatch(std::move(*sub), w);
				}
				sub = &*child;
				child++;
				sub->fieldName = "[" + std::to_string(nbIter) + "]";
				sub->address = mapNode + myVal.address;
				sub->CopyTypeInfo(pairTemplate);
				nbIter++;
				nbIterGuard++;

				rightNode = 0;
				ReadMemory(mapNode + 2*ptrSize, &rightNode, ptrSize, &cb);
				if (rightNode != myHeadAddress)
				{
					if (child == w.children.end())
					{
						sub = new TypedValueTree();
						sub->offset = nbIter;
						child = insert_subwatch(std::move(*sub), w);
					}
					sub = &*child;
					child++;
					sub->fieldName = "[" + std::to_string(nbIter) + "]";
					sub->address = rightNode + myVal.address;
					sub->CopyTypeInfo(pairTemplate);
					nbIter++;
					nbIterGuard++;
				}
				iterState = 'u'; // up
			}
			else
			{
				leftNode = mapNode;
				mapNode = 0;
				ReadMemory(leftNode, &mapNode, ptrSize, &cb); // move to left child
			}
		}

		if (iterState == 'u')
		{
			parentNode = 0;
			ReadMemory(mapNode + ptrSize, &parentNode, ptrSize, &cb);
			if (parentNode == myHeadAddress)
				break; // end of iteration
			leftNode = 0;
			ReadMemory(parentNode, &leftNode, ptrSize, &cb);
			if (mapNode == leftNode) // current node is the left child of its parent
			{
				mapNode = parentNode;
				if (child == w.children.end())
				{
					sub = new TypedValueTree();
					sub->offset = nbIter;
					child = insert_subwatch(std::move(*sub), w);
				}
				sub = &*child;
				child++;
				sub->fieldName = "[" + std::to_string(nbIter) + "]";
				sub->address = mapNode + myVal.address;
				sub->CopyTypeInfo(pairTemplate);
				nbIter++;
				nbIterGuard++;

				rightNode = 0;
				ReadMemory(mapNode + 2*ptrSize, &rightNode, ptrSize, &cb);
				if (rightNode != myHeadAddress)
				{
					mapNode = rightNode;
					iterState = 'd';
				}
			}
			else
				mapNode = parentNode;

		}
		nbIterGuard++; // just in case
	}

	if (child != w.children.end())
		w.Prune(child);
	
	return S_OK;
}

ULONG64 listNext(ULONG64 nodeAddr)
{
	ULONG64 nextAddress = 0;
	const int ptrSize = sizeof(int*);
	ReadMemory(nodeAddr, &nextAddress, ptrSize, 0);
	return nextAddress;
}

// TODO merge with FindVectorFirst
Field FindListHead(TypedValueTree& map, bool myHead,
						/*out*/ ULONG64& myHeadAddress)
{
	if (myHead)
	{
		myHeadAddress = map.GetAddressOfData();
		return map.FindField("_Myval");
	}

	TypedValueTree v;
	Field f = map.FindField("_Mypair");
	if (f.TypeId)
	{
		v.FromField(f, map.GetAddressOfData());
		v.FillFields();
		f = v.FindField("_Myval2");
		v.FromField(f, v.GetAddressOfData());
		v.FillFields();
		f = v.FindField("_Myhead");
		v.FromField(f, v.GetAddressOfData());
	}
	else
		v.FromField(map.FindField("_Myhead"), map.GetAddressOfData());

	myHeadAddress = v.GetAddressOfData();
	v.FillFields();
	return v.FindField("_Myval");
	// 	if (myHeadWatch.fields.empty())
	//myHeadWatch.FillFields();
}

HRESULT expand_list(/*out*/TypedValueTree& w, bool myHead)
{
	ULONG64 myHeadAddress = 0;
	const Field& myVal = FindListHead(w, myHead, /*out*/myHeadAddress);
	if (!myVal.TypeId)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "expand_list: _Myval not found\n");
		return E_FAIL;	
	}
	w.Prune();

	const ULONG elemTypeId = (ULONG)myVal.TypeId;
	const ULONG64 pairOffset = myVal.address;

	char pairName[1024];
	g_ExtSymbols->GetTypeName(myVal.module, elemTypeId, /*out*/pairName, 1024, 0);

	int ptrSize = sizeof(long*);
	ULONG64 addr = myHeadAddress;
	unsigned int nbIter = 0;
	while ( (addr=listNext(addr))!=myHeadAddress && nbIter<200 ) // skip first empty head
	{
		TypedValueTree* sub = new TypedValueTree();
		sub->fieldName = "[" + std::to_string(nbIter) + "]";
		sub->typeId = elemTypeId;
		sub->type = pairName;
		sub->module = myVal.module;
		sub->address = addr + pairOffset;
		sub->FillFields();
		sub->offset = nbIter;
		sub->starCount = 0; // it's the pair itself, not a pointer to it
		sub->dereferences = 0;
		insert_subwatch(std::move(*sub), w);
		nbIter++;
	}
	
	return S_OK;
}

void TypedValueTree::FillFieldsAndChildren()
{
	if (!this->expanded && this->fields.empty()) // TODO : when recompute subwatches ? for std containers, stepping can change the number of children
		this->FillFields();

	this->expanded = true;

	size_t len = this->type.length();
	if (this->type == "char[]")
		return; // this string will be handled in TypedValueTree::Print
	else if (this->fArray)
	{
		expand_array(this);
	}
	else if (this->type.compare(0, 12, "std::vector<") == 0)
	{
		expand_vector(*this);
	}
	else if (this->type.compare(0, 18, "stlpd_std::vector<") == 0)
	{
		expand_vector(*this);
	}
	else if (strncmp(this->fieldName.c_str(), "_Myfirst", 8) == 0) // subclasses of std::vector
	{
		this->typeId = this->parent->typeId;
		this->address = this->parent->address;
		this->fields = this->parent->fields;
		this->fieldCount = this->fields.size();
		expand_vector(*this);
		this->fields.clear();
		this->fieldCount = 0;
	}
	else if (this->type.compare(0, 10, "std::list<") == 0)
	{
		expand_list(*this, false);
	}
	else if (this->type.compare(0, 9, "std::map<") == 0
			|| this->type.compare(0, 9, "std::set<") == 0)
	{
		expand_map(*this, false);
	}
	else if (strncmp(this->fieldName.c_str(), "_Myhead", 7) == 0)
	{
		// Subclasses of std::map or std::list, where the _Myhead field was clicked to expand
		if (this->type.compare(0, 10, "std::_List") == 0)
			expand_list(*this, true);
		else
			expand_map(*this, true);
		
		this->fieldName = "_Myhead";
	}
	else if (this->type.compare(0, 25, "std::_Tree_const_iterator") == 0
			|| this->type.compare(0, 19, "std::_Tree_iterator") == 0)
	{
		expand_iterator(this, true);
	}
	else if (this->type.compare(0, 21, "std::_Vector_iterator") == 0
			|| this->type.compare(0, 27, "std::_Vector_const_iterator") == 0)
	{
		expand_iterator(this, false);
	}
	else if (this->starCount - this->dereferences >= 2)
	{
		// double-pointer expand
		// TRY SymGetTypeInfo BASE TYPE

		if (children.empty())
			insert_subwatch(std::move(*new TypedValueTree()), *this);
		TypedValueTree* sub = &this->children[0];
		sub->Prune();
		sub->fieldName = "[0]";
		sub->offset = 0;
		sub->type = this->type;
		sub->fPointer = true;
		sub->fStruct = false;
		sub->expanded = (this->starCount - this->dereferences == 2);
		// cut one star
		for (size_t i = sub->type.length() - 1; i >= 0; i--)
		{
			if (sub->type[i] == '*')
			{
				sub->type.resize(i);
				break;
			}
		}
		
		sub->starCount = this->starCount;
		sub->dereferences = this->dereferences + 1;
		sub->typeId = this->typeId;
		sub->module = this->module;

		ULONG cb;
		sub->address = 0;
		const int ptrSize = sizeof(long*);
		ReadMemory(this->address, &sub->address, ptrSize, &cb);

		sub->FillFields(); // same fields as the parent, could use them instead
	}
}

TypedValueTree* TypedValueTree::NewSubWatch(long offset)
{
	ULONG cb;
	char type[2048];
	TypedValueTree* w = new TypedValueTree();
	w->expanded = false;
	w->offset = offset;

	Field fieldDesc;
	if (GetField(w->offset, /*out*/fieldDesc) != S_OK)
		return 0;
	
	w->fieldName = fieldDesc.fName;
	w->module = fieldDesc.module;
	w->typeId = fieldDesc.TypeId;
	w->address = fieldDesc.address;
	w->fPointer = fieldDesc.fPointer;
	w->fStruct = fieldDesc.fStruct;
	w->fArray = fieldDesc.fArray;
	if (g_ExtSymbols->GetTypeName(w->module, (ULONG)w->typeId, /*out*/type, 2048, &cb) != S_OK)
	{
		g_ExtControl->Output(DEBUG_OUTPUT_NORMAL, "Couldn't get type name %d\n", w->typeId);
		return 0;
	}
	w->type = type;
	w->starCount = countFinalStars(w->type.c_str());

	return &*insert_subwatch(std::move(*w), *this);
}
