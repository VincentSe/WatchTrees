/*++

Copyright (c) 2017  Vincent Semeria

--*/


#pragma once

#include <dbgeng.h>
#include <string>
#include <vector>
#include <memory>

struct LightField
{
	char fName[128];
	ULONG TypeId{};
	ULONG64 module{};
	ULONG64 address{}; // memoryOffsetInParent;
	bool fStruct{};
	bool fPointer{};
	bool fArray{};
	bool fStatic{};
	ULONG size{};
};

// The sizes of field names are not known a priori, use this struct to pretty print a posteriori, like alignment
struct WatchLine
{
	std::string name, value, type;
	ULONG64 cStrAddr = 0; // when type==string, this is the string's value
};

// No value in the struct, values are evaluated in Print
class TypedValueTree
{
public:
	TypedValueTree() = default;
	TypedValueTree(const TypedValueTree& other) = delete; // deep copies are useless in this project
	TypedValueTree& operator=(const TypedValueTree& other) = delete;
	TypedValueTree& operator=(TypedValueTree&& other);
	TypedValueTree(TypedValueTree&& other);

	void Prune();
	void Prune(std::vector<TypedValueTree>::iterator fromChild);
	void Print(long indent, std::vector<WatchLine>& output); // updates addresses during the print
	void CopyTypeInfo(const TypedValueTree& other);

	// TODO merge those 2 methods
	void FillFields(); // Get symbols SymTagData
	void FillFieldsAndChildren(); // Transform std containers, adding children watches instead of native fields

	HRESULT GetField(unsigned long fieldOffset, /*out*/LightField& fieldDesc) const; // Convert a SymTagData to a type symbol
	LightField FindField(const char* fieldName) const;
	void FromField(const LightField& field, ULONG64 addr);
	ULONG64 GetAddressOfData() const; // dereference this->address for pointer types

	char GetExpandCharacter() const; // the + or - to click

	// Whether this watch should print its C++ fields, or some other representation (like vectors or maps)
	bool TransformedType() const;
	std::string GetDeepType(unsigned __int64 addr) const;

	TypedValueTree* NewSubWatch(long offset);
	TypedValueTree* FindWatchPath(const unsigned int* path, int pathLength);
	
	std::string fieldName; // for struct and classes
	unsigned __int64 module {}; // address in the debugee's memory where the module is loaded
	ULONG typeId {};
	std::string type; // can be long types like complex maps
	bool fPointer {}, fStruct {}, fArray {};
	unsigned long starCount {}; // workaround because dbgeng cannot lookup pointer types by string

	// IG_DUMP_SYMBOL_INFO on a pointer of any order, like Foo****, will give fields of Foo correctly.
	// Only need to track the number of dereferences
	unsigned long dereferences{};
	bool expanded = true;

	unsigned __int64 address{};

	// For virtual inheritance, sometimes the data are before the pointed address.
	// Besides, address watches like "&x" have no this->address, 
	// their evaluation yields an address that is the watch's value, store it here too.
	unsigned __int64 dynamicDereference{};

	// fields compete with children below. fields are native C++ fields, whereas children are subwatches,
	// created when clicking on the expand signs, or by transforming types such as std containers.
	std::vector<LightField> fields;
	size_t fieldCount{}; // weird for arrays
	unsigned long TypeSize{};

	unsigned long offset {}; // class or struct's field number in parent watch
	std::vector<TypedValueTree> children;
	TypedValueTree* parent {};
};

struct Watch
{
	Watch() = default;
	Watch(Watch&& other);
	Watch& operator=(Watch&& other);

	std::string expr;
	TypedValueTree valTree;
	
	HRESULT evaluate();
	void Print(std::vector<WatchLine>& output);
};

extern std::vector<Watch> gWatches; 
