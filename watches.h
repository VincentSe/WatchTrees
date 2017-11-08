/*++

Copyright (c) 2017  Vincent Semeria

--*/


#pragma once

#include <dbgeng.h>
#include <string>
#include <vector>
#include <memory>

/**
Describes a field of a C++ class or struct.
*/
struct Field
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

	// For fields that represent a virtual super class of parent's class.
	// It is the number of this field in its parent's vbtable, or -1 if not a virtual super class.
	ULONG virtualSuperClassIndex = -1;
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

	HRESULT GetField(unsigned long fieldOffset, /*out*/Field& fieldDesc) const; // Convert a SymTagData to a type symbol
	Field FindField(const char* fieldName) const;
	void FromField(const Field& field, ULONG64 addr);
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
	unsigned long starCount {}; // special treatment for double pointers

	// IG_DUMP_SYMBOL_INFO on a pointer of any order, like Foo****, will give fields of Foo correctly.
	// Only need to track the number of dereferences
	unsigned long dereferences{};
	bool expanded = true;

	unsigned __int64 address{}; // for a pointer int* x, address is &x, not x.

	// fields compete with children below. fields are native C++ fields, whereas children are subwatches,
	// created when clicking on the expand signs, or by transforming types such as std containers.
	std::vector<Field> fields;
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
