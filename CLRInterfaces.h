#pragma once

/**
CLR Interfaces taken from
https://github.com/dotnet/coreclr/blob/master/src/pal/prebuilt/inc/sospriv.h
https://github.com/dotnet/coreclr/src/pal/prebuilt/inc/xclrdata.h
*/

typedef ULONG64 CLRDATA_ADDRESS;

struct DacpUsefulGlobalsData // : ZeroInit<DacpUsefulGlobalsData>
{
	CLRDATA_ADDRESS ArrayMethodTable;
	CLRDATA_ADDRESS StringMethodTable;
	CLRDATA_ADDRESS ObjectMethodTable;
	CLRDATA_ADDRESS ExceptionMethodTable;
	CLRDATA_ADDRESS FreeMethodTable;
};

typedef BOOL(*VISITRCWFORCLEANUP)(
	CLRDATA_ADDRESS RCW,
	CLRDATA_ADDRESS Context,
	CLRDATA_ADDRESS Thread,
	BOOL bIsFreeThreaded,
	LPVOID token);

typedef void(*MODULEMAPTRAVERSE)(
	UINT index,
	CLRDATA_ADDRESS methodTable,
	LPVOID token);

typedef void(*VISITHEAP)(
	CLRDATA_ADDRESS blockData,
	size_t blockSize,
	BOOL blockIsCurrentBlock);

typedef BOOL(*DUMPEHINFO)(
	UINT clauseIndex,
	UINT totalClauses,
	struct DACEHInfo *pEHInfo,
	LPVOID token);


typedef struct _SOSHandleData
{
	CLRDATA_ADDRESS AppDomain;
	CLRDATA_ADDRESS Handle;
	CLRDATA_ADDRESS Secondary;
	unsigned int Type;
	BOOL StrongReference;
	unsigned int RefCount;
	unsigned int JupiterRefCount;
	BOOL IsPegged;
} 	SOSHandleData;

typedef /* [public][public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0012_0001
{
	CLRDATA_SOURCE_TYPE_INVALID = 0
} 	CLRDataSourceType;

typedef /* [public][public][public][public][public] */ struct __MIDL___MIDL_itf_xclrdata_0000_0001_0006
{
	ULONG64 Data[8];
} 	CLRDATA_FOLLOW_STUB_BUFFER;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_xclrdata_0000_0012_0003
{
	ULONG32 ilOffset;
	CLRDATA_ADDRESS startAddress;
	CLRDATA_ADDRESS endAddress;
	CLRDataSourceType type;
} 	CLRDATA_IL_ADDRESS_MAP;

typedef /* [public][public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0012_0005
{
	CLRDATA_METHDEF_IL = 0
} 	CLRDataMethodDefinitionExtentType;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_xclrdata_0000_0012_0006
{
	CLRDATA_ADDRESS startAddress;
	CLRDATA_ADDRESS endAddress;
	ULONG32 enCVersion;
	CLRDataMethodDefinitionExtentType type;
} 	CLRDATA_METHDEF_EXTENT;

typedef
enum SOSStackSourceType
{
	SOS_StackSourceIP = 0,
	SOS_StackSourceFrame = (SOS_StackSourceIP + 1)
} 	SOSStackSourceType;

typedef struct _SOS_StackRefError
{
	SOSStackSourceType SourceType;
	CLRDATA_ADDRESS Source;
	CLRDATA_ADDRESS StackPointer;
} 	SOSStackRefError;

typedef struct _SOS_StackRefData
{
	BOOL HasRegisterInformation;
	int Register;
	int Offset;
	CLRDATA_ADDRESS Address;
	CLRDATA_ADDRESS Object;
	unsigned int Flags;
	SOSStackSourceType SourceType;
	CLRDATA_ADDRESS Source;
	CLRDATA_ADDRESS StackPointer;
} 	SOSStackRefData;

typedef /* [public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0001_0004
{
	CLRDATA_ADDRESS_UNRECOGNIZED = 0,
	CLRDATA_ADDRESS_MANAGED_METHOD = (CLRDATA_ADDRESS_UNRECOGNIZED + 1),
	CLRDATA_ADDRESS_RUNTIME_MANAGED_CODE = (CLRDATA_ADDRESS_MANAGED_METHOD + 1),
	CLRDATA_ADDRESS_RUNTIME_UNMANAGED_CODE = (CLRDATA_ADDRESS_RUNTIME_MANAGED_CODE + 1),
	CLRDATA_ADDRESS_GC_DATA = (CLRDATA_ADDRESS_RUNTIME_UNMANAGED_CODE + 1),
	CLRDATA_ADDRESS_RUNTIME_MANAGED_STUB = (CLRDATA_ADDRESS_GC_DATA + 1),
	CLRDATA_ADDRESS_RUNTIME_UNMANAGED_STUB = (CLRDATA_ADDRESS_RUNTIME_MANAGED_STUB + 1)
} 	CLRDataAddressType;

typedef /* [public][public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0008_0002
{
	CLRDATA_MODULE_PE_FILE = 0,
	CLRDATA_MODULE_PREJIT_FILE = (CLRDATA_MODULE_PE_FILE + 1),
	CLRDATA_MODULE_MEMORY_STREAM = (CLRDATA_MODULE_PREJIT_FILE + 1),
	CLRDATA_MODULE_OTHER = (CLRDATA_MODULE_MEMORY_STREAM + 1)
} 	CLRDataModuleExtentType;

typedef /* [public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0018_0002
{
	CLRDATA_EXBASE_EXCEPTION = 0,
	CLRDATA_EXBASE_OUT_OF_MEMORY = (CLRDATA_EXBASE_EXCEPTION + 1),
	CLRDATA_EXBASE_INVALID_ARGUMENT = (CLRDATA_EXBASE_OUT_OF_MEMORY + 1)
} 	CLRDataBaseExceptionType;

typedef /* [public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0001_0009
{
	CLRNATIVEIMAGE_PE_INFO = 0x1,
	CLRNATIVEIMAGE_COR_INFO = 0x2,
	CLRNATIVEIMAGE_FIXUP_TABLES = 0x4,
	CLRNATIVEIMAGE_FIXUP_HISTOGRAM = 0x8,
	CLRNATIVEIMAGE_MODULE = 0x10,
	CLRNATIVEIMAGE_METHODS = 0x20,
	CLRNATIVEIMAGE_DISASSEMBLE_CODE = 0x40,
	CLRNATIVEIMAGE_IL = 0x80,
	CLRNATIVEIMAGE_METHODTABLES = 0x100,
	CLRNATIVEIMAGE_NATIVE_INFO = 0x200,
	CLRNATIVEIMAGE_MODULE_TABLES = 0x400,
	CLRNATIVEIMAGE_FROZEN_SEGMENT = 0x800,
	CLRNATIVEIMAGE_PE_FILE = 0x1000,
	CLRNATIVEIMAGE_GC_INFO = 0x2000,
	CLRNATIVEIMAGE_EECLASSES = 0x4000,
	CLRNATIVEIMAGE_NATIVE_TABLES = 0x8000,
	CLRNATIVEIMAGE_PRECODES = 0x10000,
	CLRNATIVEIMAGE_TYPEDESCS = 0x20000,
	CLRNATIVEIMAGE_VERBOSE_TYPES = 0x40000,
	CLRNATIVEIMAGE_METHODDESCS = 0x80000,
	CLRNATIVEIMAGE_METADATA = 0x100000,
	CLRNATIVEIMAGE_DISABLE_NAMES = 0x200000,
	CLRNATIVEIMAGE_DISABLE_REBASING = 0x400000,
	CLRNATIVEIMAGE_SLIM_MODULE_TBLS = 0x800000,
	CLRNATIVEIMAGE_RESOURCES = 0x1000000,
	CLRNATIVEIMAGE_FILE_OFFSET = 0x2000000,
	CLRNATIVEIMAGE_DEBUG_TRACE = 0x4000000,
	CLRNATIVEIMAGE_RELOCATIONS = 0x8000000,
	CLRNATIVEIMAGE_FIXUP_THUNKS = 0x10000000,
	CLRNATIVEIMAGE_DEBUG_COVERAGE = 0x80000000
} 	CLRNativeImageDumpOptions;

typedef /* [public][public] */ struct __MIDL___MIDL_itf_xclrdata_0000_0008_0003
{
	CLRDATA_ADDRESS base;
	ULONG32 length;
	CLRDataModuleExtentType type;
} 	CLRDATA_MODULE_EXTENT;

typedef /* [public][public][public] */ struct __MIDL___MIDL_itf_xclrdata_0000_0000_0001
{
	CLRDATA_ADDRESS startAddress;
	CLRDATA_ADDRESS endAddress;
} 	CLRDATA_ADDRESS_RANGE;

typedef /* [public][public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0015_0001
{
	CLRDATA_SIMPFRAME_UNRECOGNIZED = 0x1,
	CLRDATA_SIMPFRAME_MANAGED_METHOD = 0x2,
	CLRDATA_SIMPFRAME_RUNTIME_MANAGED_CODE = 0x4,
	CLRDATA_SIMPFRAME_RUNTIME_UNMANAGED_CODE = 0x8
} 	CLRDataSimpleFrameType;

typedef /* [public][public][public] */
enum __MIDL___MIDL_itf_xclrdata_0000_0015_0002
{
	CLRDATA_DETFRAME_UNRECOGNIZED = 0,
	CLRDATA_DETFRAME_UNKNOWN_STUB = (CLRDATA_DETFRAME_UNRECOGNIZED + 1),
	CLRDATA_DETFRAME_CLASS_INIT = (CLRDATA_DETFRAME_UNKNOWN_STUB + 1),
	CLRDATA_DETFRAME_EXCEPTION_FILTER = (CLRDATA_DETFRAME_CLASS_INIT + 1),
	CLRDATA_DETFRAME_SECURITY = (CLRDATA_DETFRAME_EXCEPTION_FILTER + 1),
	CLRDATA_DETFRAME_CONTEXT_POLICY = (CLRDATA_DETFRAME_SECURITY + 1),
	CLRDATA_DETFRAME_INTERCEPTION = (CLRDATA_DETFRAME_CONTEXT_POLICY + 1),
	CLRDATA_DETFRAME_PROCESS_START = (CLRDATA_DETFRAME_INTERCEPTION + 1),
	CLRDATA_DETFRAME_THREAD_START = (CLRDATA_DETFRAME_PROCESS_START + 1),
	CLRDATA_DETFRAME_TRANSITION_TO_MANAGED = (CLRDATA_DETFRAME_THREAD_START + 1),
	CLRDATA_DETFRAME_TRANSITION_TO_UNMANAGED = (CLRDATA_DETFRAME_TRANSITION_TO_MANAGED + 1),
	CLRDATA_DETFRAME_COM_INTEROP_STUB = (CLRDATA_DETFRAME_TRANSITION_TO_UNMANAGED + 1),
	CLRDATA_DETFRAME_DEBUGGER_EVAL = (CLRDATA_DETFRAME_COM_INTEROP_STUB + 1),
	CLRDATA_DETFRAME_CONTEXT_SWITCH = (CLRDATA_DETFRAME_DEBUGGER_EVAL + 1),
	CLRDATA_DETFRAME_FUNC_EVAL = (CLRDATA_DETFRAME_CONTEXT_SWITCH + 1),
	CLRDATA_DETFRAME_FINALLY = (CLRDATA_DETFRAME_FUNC_EVAL + 1)
} 	CLRDataDetailedFrameType;


typedef UINT32 mdToken;

typedef mdToken mdTypeDef;

typedef mdToken mdMethodDef;

typedef mdToken mdFieldDef;

typedef ULONG CorElementType;

typedef ULONG64 CLRDATA_ENUM;

typedef int T_CONTEXT;

enum ModuleMapType { TYPEDEFTOMETHODTABLE, TYPEREFTOMETHODTABLE };

enum VCSHeapType { IndcellHeap, LookupHeap, ResolveHeap, DispatchHeap, CacheEntryHeap };


struct IXCLRDataModule;
struct IXCLRDataTypeDefinition;
struct IXCLRDataMethodInstance;
struct IXCLRDataTypeInstance;
struct IXCLRDataValue;
struct IXCLRDataProcess;
struct IXCLRDataTask;
struct IXCLRDataAssembly;
struct IXCLRDataMethodDefinition;
struct IXCLRDataDisplay;
struct IXCLRLibrarySupport;
struct IXCLRDisassemblySupport;
struct IXCLRDataAppDomain;
struct IXCLRDataExceptionNotification;

struct DacpReJitData //: ZeroInit<DacpReJitData>
{
	enum Flags
	{
		kUnknown,
		kRequested,
		kActive,
		kReverted,
	};

	CLRDATA_ADDRESS                 rejitID;
	Flags                           flags;
	CLRDATA_ADDRESS                 NativeCodeAddr;
};

typedef SIZE_T(__stdcall *CDSTranslateAddrCB)(
	IXCLRDisassemblySupport *__MIDL____MIDL_itf_xclrdata_0000_00020000,
	CLRDATA_ADDRESS __MIDL____MIDL_itf_xclrdata_0000_00020001,
	wchar_t *__MIDL____MIDL_itf_xclrdata_0000_00020002,
	SIZE_T __MIDL____MIDL_itf_xclrdata_0000_00020003,
	DWORDLONG *__MIDL____MIDL_itf_xclrdata_0000_00020004);

typedef SIZE_T(__stdcall *CDSTranslateFixupCB)(
	IXCLRDisassemblySupport *__MIDL____MIDL_itf_xclrdata_0000_00020006,
	CLRDATA_ADDRESS __MIDL____MIDL_itf_xclrdata_0000_00020007,
	SIZE_T __MIDL____MIDL_itf_xclrdata_0000_00020008,
	wchar_t *__MIDL____MIDL_itf_xclrdata_0000_00020009,
	SIZE_T __MIDL____MIDL_itf_xclrdata_0000_00020010,
	DWORDLONG *__MIDL____MIDL_itf_xclrdata_0000_00020011);

typedef SIZE_T(__stdcall *CDSTranslateConstCB)(
	IXCLRDisassemblySupport *__MIDL____MIDL_itf_xclrdata_0000_00020013,
	DWORD __MIDL____MIDL_itf_xclrdata_0000_00020014,
	wchar_t *__MIDL____MIDL_itf_xclrdata_0000_00020015,
	SIZE_T __MIDL____MIDL_itf_xclrdata_0000_00020016);

typedef SIZE_T(__stdcall *CDSTranslateRegrelCB)(
	IXCLRDisassemblySupport *__MIDL____MIDL_itf_xclrdata_0000_00020018,
	unsigned int rega,
	CLRDATA_ADDRESS __MIDL____MIDL_itf_xclrdata_0000_00020019,
	wchar_t *__MIDL____MIDL_itf_xclrdata_0000_00020020,
	SIZE_T __MIDL____MIDL_itf_xclrdata_0000_00020021,
	DWORD *__MIDL____MIDL_itf_xclrdata_0000_00020022);

MIDL_INTERFACE("75DA9E4C-BD33-43C8-8F5C-96E8A5241F57")
IXCLRDataExceptionState : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetPrevious(
		/* [out] */ IXCLRDataExceptionState **exState) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetManagedObject(
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetBaseType(
		/* [out] */ CLRDataBaseExceptionType *type) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCode(
		/* [out] */ ULONG32 *code) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetString(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *strLen,
		/* [size_is][out] */ WCHAR str[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameState(
		/* [in] */ EXCEPTION_RECORD64 *exRecord,
		/* [in] */ ULONG32 contextSize,
		/* [size_is][in] */ BYTE cxRecord[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameState2(
		/* [in] */ ULONG32 flags,
		/* [in] */ EXCEPTION_RECORD64 *exRecord,
		/* [in] */ ULONG32 contextSize,
		/* [size_is][in] */ BYTE cxRecord[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTask(
		/* [out] */ IXCLRDataTask **task) = 0;

};

MIDL_INTERFACE("5c552ab6-fc09-4cb3-8e36-22fa03c798b7")
IXCLRDataProcess : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Flush(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumTasks(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumTask(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTask **task) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumTasks(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTaskByOSThreadID(
		/* [in] */ ULONG32 osThreadID,
		/* [out] */ IXCLRDataTask **task) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTaskByUniqueID(
		/* [in] */ ULONG64 taskID,
		/* [out] */ IXCLRDataTask **task) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataProcess *process) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetManagedObject(
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDesiredExecutionState(
		/* [out] */ ULONG32 *state) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetDesiredExecutionState(
		/* [in] */ ULONG32 state) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressType(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [out] */ CLRDataAddressType *type) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRuntimeNameByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ CLRDATA_ADDRESS *displacement) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumAppDomains(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumAppDomain(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumAppDomains(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainByUniqueID(
		/* [in] */ ULONG64 id,
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumAssemblies(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumAssembly(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataAssembly **assembly) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumAssemblies(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumModules(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumModule(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumModules(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModuleByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodInstancesByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodInstanceByAddress(
		/* [in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodInstance **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodInstancesByAddress(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDataByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataValue **value,
		/* [out] */ CLRDATA_ADDRESS *displacement) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetExceptionStateByExceptionRecord(
		/* [in] */ EXCEPTION_RECORD64 *record,
		/* [out] */ IXCLRDataExceptionState **exState) = 0;

	virtual HRESULT STDMETHODCALLTYPE TranslateExceptionRecordToNotification(
		/* [in] */ EXCEPTION_RECORD64 *record,
		/* [in] */ IXCLRDataExceptionNotification *notify) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE CreateMemoryValue(
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [in] */ IXCLRDataTypeInstance *type,
		/* [in] */ CLRDATA_ADDRESS addr,
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetAllTypeNotifications(
		IXCLRDataModule *mod,
		ULONG32 flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetAllCodeNotifications(
		IXCLRDataModule *mod,
		ULONG32 flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeNotifications(
		/* [in] */ ULONG32 numTokens,
		/* [size_is][in] */ IXCLRDataModule *mods[],
		/* [in] */ IXCLRDataModule *singleMod,
		/* [size_is][in] */ mdTypeDef tokens[],
		/* [size_is][out] */ ULONG32 flags[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTypeNotifications(
		/* [in] */ ULONG32 numTokens,
		/* [size_is][in] */ IXCLRDataModule *mods[],
		/* [in] */ IXCLRDataModule *singleMod,
		/* [size_is][in] */ mdTypeDef tokens[],
		/* [size_is][in] */ ULONG32 flags[],
		/* [in] */ ULONG32 singleFlags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeNotifications(
		/* [in] */ ULONG32 numTokens,
		/* [size_is][in] */ IXCLRDataModule *mods[],
		/* [in] */ IXCLRDataModule *singleMod,
		/* [size_is][in] */ mdMethodDef tokens[],
		/* [size_is][out] */ ULONG32 flags[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetCodeNotifications(
		/* [in] */ ULONG32 numTokens,
		/* [size_is][in] */ IXCLRDataModule *mods[],
		/* [in] */ IXCLRDataModule *singleMod,
		/* [size_is][in] */ mdMethodDef tokens[],
		/* [size_is][in] */ ULONG32 flags[],
		/* [in] */ ULONG32 singleFlags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetOtherNotificationFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetOtherNotificationFlags(
		/* [in] */ ULONG32 flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodDefinitionsByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodDefinitionByAddress(
		/* [in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodDefinition **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodDefinitionsByAddress(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE FollowStub(
		/* [in] */ ULONG32 inFlags,
		/* [in] */ CLRDATA_ADDRESS inAddr,
		/* [in] */ CLRDATA_FOLLOW_STUB_BUFFER *inBuffer,
		/* [out] */ CLRDATA_ADDRESS *outAddr,
		/* [out] */ CLRDATA_FOLLOW_STUB_BUFFER *outBuffer,
		/* [out] */ ULONG32 *outFlags) = 0;

	virtual HRESULT STDMETHODCALLTYPE FollowStub2(
		/* [in] */ IXCLRDataTask *task,
		/* [in] */ ULONG32 inFlags,
		/* [in] */ CLRDATA_ADDRESS inAddr,
		/* [in] */ CLRDATA_FOLLOW_STUB_BUFFER *inBuffer,
		/* [out] */ CLRDATA_ADDRESS *outAddr,
		/* [out] */ CLRDATA_FOLLOW_STUB_BUFFER *outBuffer,
		/* [out] */ ULONG32 *outFlags) = 0;

	virtual HRESULT STDMETHODCALLTYPE DumpNativeImage(
		/* [in] */ CLRDATA_ADDRESS loadedBase,
		/* [in] */ LPCWSTR name,
		/* [in] */ IXCLRDataDisplay *display,
		/* [in] */ IXCLRLibrarySupport *libSupport,
		/* [in] */ IXCLRDisassemblySupport *dis) = 0;

};

MIDL_INTERFACE("286CA186-E763-4F61-9760-487D43AE4341")
ISOSEnum : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Skip(
		/* [in] */ unsigned int count) = 0;

	virtual HRESULT STDMETHODCALLTYPE Reset(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCount(
		/* [out] */ unsigned int *pCount) = 0;

};

MIDL_INTERFACE("3E269830-4A2B-4301-8EE2-D6805B29B2FA")
ISOSHandleEnum : public ISOSEnum
{
public:
	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ unsigned int count,
		/* [length_is][size_is][out] */ SOSHandleData handles[],
		/* [out] */ unsigned int *pNeeded) = 0;

};

MIDL_INTERFACE("7CA04601-C702-4670-A63C-FA44F7DA7BD5")
IXCLRDataAppDomain : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetProcess(
		/* [out] */ IXCLRDataProcess **process) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetUniqueID(
		/* [out] */ ULONG64 *id) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataAppDomain *appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetManagedObject(
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

};

MIDL_INTERFACE("271498C2-4085-4766-BC3A-7F8ED188A173")
IXCLRDataFrame : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetFrameType(
		/* [out] */ CLRDataSimpleFrameType *simpleType,
		/* [out] */ CLRDataDetailedFrameType *detailedType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetContext(
		/* [in] */ ULONG32 contextFlags,
		/* [in] */ ULONG32 contextBufSize,
		/* [out] */ ULONG32 *contextSize,
		/* [size_is][out] */ BYTE contextBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomain(
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumArguments(
		/* [out] */ ULONG32 *numArgs) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetArgumentByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataValue **arg,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumLocalVariables(
		/* [out] */ ULONG32 *numLocals) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLocalVariableByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataValue **localVariable,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeName(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodInstance(
		/* [out] */ IXCLRDataMethodInstance **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumTypeArguments(
		/* [out] */ ULONG32 *numTypeArgs) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeArgumentByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataTypeInstance **typeArg) = 0;

};

MIDL_INTERFACE("E59D8D22-ADA7-49a2-89B5-A415AFCFC95F")
IXCLRDataStackWalk : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetContext(
		/* [in] */ ULONG32 contextFlags,
		/* [in] */ ULONG32 contextBufSize,
		/* [out] */ ULONG32 *contextSize,
		/* [size_is][out] */ BYTE contextBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetContext(
		/* [in] */ ULONG32 contextSize,
		/* [size_is][in] */ BYTE context[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE Next(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStackSizeSkipped(
		/* [out] */ ULONG64 *stackSizeSkipped) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFrameType(
		/* [out] */ CLRDataSimpleFrameType *simpleType,
		/* [out] */ CLRDataDetailedFrameType *detailedType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFrame(
		/* [out] */ IXCLRDataFrame **frame) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetContext2(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 contextSize,
		/* [size_is][in] */ BYTE context[]) = 0;

};

MIDL_INTERFACE("96EC93C7-1000-4e93-8991-98D8766E6666")
IXCLRDataValue : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddress(
		/* [out] */ CLRDATA_ADDRESS *address) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSize(
		/* [out] */ ULONG64 *size) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetBytes(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *dataSize,
		/* [size_is][out] */ BYTE buffer[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetBytes(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *dataSize,
		/* [size_is][in] */ BYTE buffer[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetType(
		/* [out] */ IXCLRDataTypeInstance **typeInstance) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumFields(
		/* [out] */ ULONG32 *numFields) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumFields2(
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataTypeInstance *fromType,
		/* [out] */ ULONG32 *numFields) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumFields(
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataTypeInstance *fromType,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumField(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumFields(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumFieldsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 nameFlags,
		/* [in] */ ULONG32 fieldFlags,
		/* [in] */ IXCLRDataTypeInstance *fromType,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumFieldByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **field,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumFieldsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldByToken(
		/* [in] */ mdFieldDef token,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssociatedValue(
		/* [out] */ IXCLRDataValue **assocValue) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssociatedType(
		/* [out] */ IXCLRDataTypeInstance **assocType) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetString(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *strLen,
		/* [size_is][out] */ WCHAR str[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetArrayProperties(
		/* [out] */ ULONG32 *rank,
		/* [out] */ ULONG32 *totalElements,
		/* [in] */ ULONG32 numDim,
		/* [size_is][out] */ ULONG32 dims[],
		/* [in] */ ULONG32 numBases,
		/* [size_is][out] */ LONG32 bases[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetArrayElement(
		/* [in] */ ULONG32 numInd,
		/* [size_is][in] */ LONG32 indices[],
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumField2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumFieldByName2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **field,
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldByToken2(
		/* [in] */ IXCLRDataModule *tokenScope,
		/* [in] */ mdFieldDef token,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumLocations(
		/* [out] */ ULONG32 *numLocs) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLocationByIndex(
		/* [in] */ ULONG32 loc,
		/* [out] */ ULONG32 *flags,
		/* [out] */ CLRDATA_ADDRESS *arg) = 0;

};

MIDL_INTERFACE("2D95A079-42A1-4837-818F-0B97D7048E0E")
IXCLRDataExceptionNotification : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE OnCodeGenerated(
		/* [in] */ IXCLRDataMethodInstance *method) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnCodeDiscarded(
		/* [in] */ IXCLRDataMethodInstance *method) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnProcessExecution(
		/* [in] */ ULONG32 state) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnTaskExecution(
		/* [in] */ IXCLRDataTask *task,
		/* [in] */ ULONG32 state) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnModuleLoaded(
		/* [in] */ IXCLRDataModule *mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnModuleUnloaded(
		/* [in] */ IXCLRDataModule *mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnTypeLoaded(
		/* [in] */ IXCLRDataTypeInstance *typeInst) = 0;

	virtual HRESULT STDMETHODCALLTYPE OnTypeUnloaded(
		/* [in] */ IXCLRDataTypeInstance *typeInst) = 0;

};

MIDL_INTERFACE("1F0F7134-D3F3-47DE-8E9B-C2FD358A2936")
IXCLRDisassemblySupport : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE SetTranslateAddrCallback(
		/* [in] */ CDSTranslateAddrCB cb) = 0;

	virtual HRESULT STDMETHODCALLTYPE PvClientSet(
		/* [in] */ void *pv) = 0;

	virtual SIZE_T STDMETHODCALLTYPE CbDisassemble(
		CLRDATA_ADDRESS __MIDL__IXCLRDisassemblySupport0000,
		const void *__MIDL__IXCLRDisassemblySupport0001,
		SIZE_T __MIDL__IXCLRDisassemblySupport0002) = 0;

	virtual SIZE_T STDMETHODCALLTYPE Cinstruction(void) = 0;

	virtual BOOL STDMETHODCALLTYPE FSelectInstruction(
		SIZE_T __MIDL__IXCLRDisassemblySupport0003) = 0;

	virtual SIZE_T STDMETHODCALLTYPE CchFormatInstr(
		wchar_t *__MIDL__IXCLRDisassemblySupport0004,
		SIZE_T __MIDL__IXCLRDisassemblySupport0005) = 0;

	virtual void *STDMETHODCALLTYPE PvClient(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTranslateFixupCallback(
		/* [in] */ CDSTranslateFixupCB cb) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTranslateConstCallback(
		/* [in] */ CDSTranslateConstCB cb) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTranslateRegrelCallback(
		/* [in] */ CDSTranslateRegrelCB cb) = 0;

	virtual BOOL STDMETHODCALLTYPE TargetIsAddress(void) = 0;

};

MIDL_INTERFACE("E5F3039D-2C0C-4230-A69E-12AF1C3E563C")
IXCLRLibrarySupport : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE LoadHardboundDependency(
		const WCHAR *name,
		REFGUID mvid,
		/* [out] */ SIZE_T *loadedBase) = 0;

	virtual HRESULT STDMETHODCALLTYPE LoadSoftboundDependency(
		const WCHAR *name,
		const BYTE *assemblymetadataBinding,
		const BYTE *hash,
		ULONG hashLength,
		/* [out] */ SIZE_T *loadedBase) = 0;

};

MIDL_INTERFACE("A3C1704A-4559-4a67-8D28-E8F4FE3B3F62")
IXCLRDataDisplay : public IUnknown
{
public:
	virtual HRESULT STDMETHODVCALLTYPE ErrorPrintF(
		const char *const fmt,
		...) = 0;

	virtual HRESULT STDMETHODCALLTYPE NativeImageDimensions(
		SIZE_T base,
		SIZE_T size,
		DWORD sectionAlign) = 0;

	virtual HRESULT STDMETHODCALLTYPE Section(
		const char *const name,
		SIZE_T rva,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDumpOptions(
		/* [out] */ CLRNativeImageDumpOptions *pOptions) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartDocument(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndDocument(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartCategory(
		const char *const name) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndCategory(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartElement(
		const char *const name) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndElement(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartVStructure(
		const char *const name) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartVStructureWithOffset(
		const char *const name,
		unsigned int fieldOffset,
		unsigned int fieldSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndVStructure(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartTextElement(
		const char *const name) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndTextElement(void) = 0;

	virtual HRESULT STDMETHODVCALLTYPE WriteXmlText(
		const char *const fmt,
		...) = 0;

	virtual HRESULT STDMETHODVCALLTYPE WriteXmlTextBlock(
		const char *const fmt,
		...) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteEmptyElement(
		const char *const element) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementPointer(
		const char *const element,
		SIZE_T ptr) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementPointerAnnotated(
		const char *const element,
		SIZE_T ptr,
		const WCHAR *const annotation) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementAddress(
		const char *const element,
		SIZE_T base,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementAddressNamed(
		const char *const element,
		const char *const name,
		SIZE_T base,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementAddressNamedW(
		const char *const element,
		const WCHAR *const name,
		SIZE_T base,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementString(
		const char *const element,
		const char *const data) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementStringW(
		const char *const element,
		const WCHAR *const data) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementInt(
		const char *const element,
		int value) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementUInt(
		const char *const element,
		DWORD value) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementEnumerated(
		const char *const element,
		DWORD value,
		const WCHAR *const mnemonic) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementIntWithSuppress(
		const char *const element,
		int value,
		int suppressIfEqual) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteElementFlag(
		const char *const element,
		BOOL flag) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartArray(
		const char *const name,
		const WCHAR *const fmt) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndArray(
		const char *const countPrefix) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartList(
		const WCHAR *const fmt) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndList(void) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartArrayWithOffset(
		const char *const name,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		const WCHAR *const fmt) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldString(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		const char *const data) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldStringW(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		const WCHAR *const data) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldPointer(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		SIZE_T ptr) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldPointerWithSize(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		SIZE_T ptr,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldInt(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		int value) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldUInt(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		DWORD value) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldEnumerated(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		DWORD value,
		const WCHAR *const mnemonic) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldEmpty(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldFlag(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		BOOL flag) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldPointerAnnotated(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		SIZE_T ptr,
		const WCHAR *const annotation) = 0;

	virtual HRESULT STDMETHODCALLTYPE WriteFieldAddress(
		const char *const element,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		SIZE_T base,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartStructure(
		const char *const name,
		SIZE_T ptr,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartStructureWithNegSpace(
		const char *const name,
		SIZE_T ptr,
		SIZE_T startPtr,
		SIZE_T totalSize) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartStructureWithOffset(
		const char *const name,
		unsigned int fieldOffset,
		unsigned int fieldSize,
		SIZE_T ptr,
		SIZE_T size) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndStructure(void) = 0;

};

MIDL_INTERFACE("A5B0BEEA-EC62-4618-8012-A24FFC23934C")
IXCLRDataTask : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetProcess(
		/* [out] */ IXCLRDataProcess **process) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentAppDomain(
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetUniqueID(
		/* [out] */ ULONG64 *id) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataTask *task) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetManagedObject(
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDesiredExecutionState(
		/* [out] */ ULONG32 *state) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetDesiredExecutionState(
		/* [in] */ ULONG32 state) = 0;

	virtual HRESULT STDMETHODCALLTYPE CreateStackWalk(
		/* [in] */ ULONG32 flags,
		/* [out] */ IXCLRDataStackWalk **stackWalk) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetOSThreadID(
		/* [out] */ ULONG32 *id) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetContext(
		/* [in] */ ULONG32 contextFlags,
		/* [in] */ ULONG32 contextBufSize,
		/* [out] */ ULONG32 *contextSize,
		/* [size_is][out] */ BYTE contextBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetContext(
		/* [in] */ ULONG32 contextSize,
		/* [size_is][in] */ BYTE context[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCurrentExceptionState(
		/* [out] */ IXCLRDataExceptionState **exception) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLastExceptionState(
		/* [out] */ IXCLRDataExceptionState **exception) = 0;

};

MIDL_INTERFACE("4D078D91-9CB3-4b0d-97AC-28C8A5A82597")
IXCLRDataTypeInstance : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodInstances(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodInstance(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodInstance **methodInstance) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodInstances(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodInstancesByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodInstanceByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodInstance **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodInstancesByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumStaticFields(
		/* [out] */ ULONG32 *numFields) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStaticFieldByIndex(
		/* [in] */ ULONG32 index,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumStaticFieldsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumStaticFieldByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumStaticFieldsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumTypeArguments(
		/* [out] */ ULONG32 *numTypeArgs) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeArgumentByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataTypeInstance **typeArg) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModule(
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDefinition(
		/* [out] */ IXCLRDataTypeDefinition **typeDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataTypeInstance *type) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumStaticFields2(
		/* [in] */ ULONG32 flags,
		/* [out] */ ULONG32 *numFields) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumStaticFields(
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumStaticField(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumStaticFields(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumStaticFieldsByName2(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 nameFlags,
		/* [in] */ ULONG32 fieldFlags,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumStaticFieldByName2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumStaticFieldsByName2(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStaticFieldByToken(
		/* [in] */ mdFieldDef token,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetBase(
		/* [out] */ IXCLRDataTypeInstance **base) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumStaticField2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumStaticFieldByName3(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value,
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStaticFieldByToken2(
		/* [in] */ IXCLRDataModule *tokenScope,
		/* [in] */ mdFieldDef token,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ IXCLRDataValue **field,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

};

MIDL_INTERFACE("ECD73800-22CA-4b0d-AB55-E9BA7E6318A5")
IXCLRDataMethodInstance : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetTypeInstance(
		/* [out] */ IXCLRDataTypeInstance **typeInstance) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDefinition(
		/* [out] */ IXCLRDataMethodDefinition **methodDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTokenAndScope(
		/* [out] */ mdMethodDef *token,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataMethodInstance *method) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetEnCVersion(
		/* [out] */ ULONG32 *version) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumTypeArguments(
		/* [out] */ ULONG32 *numTypeArgs) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeArgumentByIndex(
		/* [in] */ ULONG32 index,
		/* [out] */ IXCLRDataTypeInstance **typeArg) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILOffsetsByAddress(
		/* [in] */ CLRDATA_ADDRESS address,
		/* [in] */ ULONG32 offsetsLen,
		/* [out] */ ULONG32 *offsetsNeeded,
		/* [size_is][out] */ ULONG32 ilOffsets[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressRangesByILOffset(
		/* [in] */ ULONG32 ilOffset,
		/* [in] */ ULONG32 rangesLen,
		/* [out] */ ULONG32 *rangesNeeded,
		/* [size_is][out] */ CLRDATA_ADDRESS_RANGE addressRanges[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILAddressMap(
		/* [in] */ ULONG32 mapLen,
		/* [out] */ ULONG32 *mapNeeded,
		/* [size_is][out] */ CLRDATA_IL_ADDRESS_MAP maps[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumExtents(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumExtent(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ CLRDATA_ADDRESS_RANGE *extent) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumExtents(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRepresentativeEntryAddress(
		/* [out] */ CLRDATA_ADDRESS *addr) = 0;

};

MIDL_INTERFACE("AAF60008-FB2C-420b-8FB1-42D244A54A97")
IXCLRDataMethodDefinition : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetTypeDefinition(
		/* [out] */ IXCLRDataTypeDefinition **typeDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumInstances(
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumInstance(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodInstance **instance) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumInstances(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTokenAndScope(
		/* [out] */ mdMethodDef *token,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataMethodDefinition *method) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLatestEnCVersion(
		/* [out] */ ULONG32 *version) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumExtents(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumExtent(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ CLRDATA_METHDEF_EXTENT *extent) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumExtents(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeNotification(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetCodeNotification(
		/* [in] */ ULONG32 flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRepresentativeEntryAddress(
		/* [out] */ CLRDATA_ADDRESS *addr) = 0;

	virtual HRESULT STDMETHODCALLTYPE HasClassOrMethodInstantiation(
		/* [out] */ BOOL *bGeneric) = 0;

};

MIDL_INTERFACE("4675666C-C275-45b8-9F6C-AB165D5C1E09")
IXCLRDataTypeDefinition : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetModule(
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodDefinitions(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodDefinition(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodDefinition **methodDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodDefinitions(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodDefinitionsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodDefinitionByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodDefinition **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodDefinitionsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDefinitionByToken(
		/* [in] */ mdMethodDef token,
		/* [out] */ IXCLRDataMethodDefinition **methodDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumInstances(
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumInstance(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeInstance **instance) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumInstances(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 flags,
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTokenAndScope(
		/* [out] */ mdTypeDef *token,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCorElementType(
		/* [out] */ CorElementType *type) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataTypeDefinition *type) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetArrayRank(
		/* [out] */ ULONG32 *rank) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetBase(
		/* [out] */ IXCLRDataTypeDefinition **base) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNumFields(
		/* [in] */ ULONG32 flags,
		/* [out] */ ULONG32 *numFields) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumFields(
		/* [in] */ ULONG32 flags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumField(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumFields(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumFieldsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 nameFlags,
		/* [in] */ ULONG32 fieldFlags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumFieldByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumFieldsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldByToken(
		/* [in] */ mdFieldDef token,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeNotification(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE SetTypeNotification(
		/* [in] */ ULONG32 flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumField2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags,
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumFieldByName2(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags,
		/* [out] */ IXCLRDataModule **tokenScope,
		/* [out] */ mdFieldDef *token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldByToken2(
		/* [in] */ IXCLRDataModule *tokenScope,
		/* [in] */ mdFieldDef token,
		/* [in] */ ULONG32 nameBufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR nameBuf[],
		/* [out] */ IXCLRDataTypeDefinition **type,
		/* [out] */ ULONG32 *flags) = 0;

};

MIDL_INTERFACE("2FA17588-43C2-46ab-9B51-C8F01E39C9AC")
IXCLRDataAssembly : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE StartEnumModules(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumModule(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumModules(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFileName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataAssembly *assembly) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumAppDomains(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumAppDomain(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumAppDomains(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDisplayName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

};

MIDL_INTERFACE("88E32849-0A0A-4cb0-9022-7CD2E9E139E2")
IXCLRDataModule : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE StartEnumAssemblies(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumAssembly(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataAssembly **assembly) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumAssemblies(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumTypeDefinitions(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumTypeDefinition(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeDefinition **typeDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumTypeDefinitions(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumTypeInstances(
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumTypeInstance(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeInstance **typeInstance) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumTypeInstances(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumTypeDefinitionsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumTypeDefinitionByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeDefinition **type) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumTypeDefinitionsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumTypeInstancesByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumTypeInstanceByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataTypeInstance **type) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumTypeInstancesByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTypeDefinitionByToken(
		/* [in] */ mdTypeDef token,
		/* [out] */ IXCLRDataTypeDefinition **typeDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodDefinitionsByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodDefinitionByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodDefinition **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodDefinitionsByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumMethodInstancesByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumMethodInstanceByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataMethodInstance **method) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumMethodInstancesByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDefinitionByToken(
		/* [in] */ mdMethodDef token,
		/* [out] */ IXCLRDataMethodDefinition **methodDefinition) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumDataByName(
		/* [in] */ LPCWSTR name,
		/* [in] */ ULONG32 flags,
		/* [in] */ IXCLRDataAppDomain *appDomain,
		/* [in] */ IXCLRDataTask *tlsTask,
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumDataByName(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataValue **value) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumDataByName(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFileName(
		/* [in] */ ULONG32 bufLen,
		/* [out] */ ULONG32 *nameLen,
		/* [size_is][out] */ WCHAR name[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFlags(
		/* [out] */ ULONG32 *flags) = 0;

	virtual HRESULT STDMETHODCALLTYPE IsSameObject(
		/* [in] */ IXCLRDataModule *mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumExtents(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumExtent(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ CLRDATA_MODULE_EXTENT *extent) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumExtents(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE Request(
		/* [in] */ ULONG32 reqCode,
		/* [in] */ ULONG32 inBufferSize,
		/* [size_is][in] */ BYTE *inBuffer,
		/* [in] */ ULONG32 outBufferSize,
		/* [size_is][out] */ BYTE *outBuffer) = 0;

	virtual HRESULT STDMETHODCALLTYPE StartEnumAppDomains(
		/* [out] */ CLRDATA_ENUM *handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumAppDomain(
		/* [out][in] */ CLRDATA_ENUM *handle,
		/* [out] */ IXCLRDataAppDomain **appDomain) = 0;

	virtual HRESULT STDMETHODCALLTYPE EndEnumAppDomains(
		/* [in] */ CLRDATA_ENUM handle) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetVersionId(
		/* [out] */ GUID *vid) = 0;

};

MIDL_INTERFACE("774F4E1B-FB7B-491B-976D-A8130FE355E9")
ISOSStackRefErrorEnum : public ISOSEnum
{
public:
	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ unsigned int count,
		/* [length_is][size_is][out] */ SOSStackRefError ref[],
		/* [out] */ unsigned int *pFetched) = 0;

};

MIDL_INTERFACE("8FA642BD-9F10-4799-9AA3-512AE78C77EE")
ISOSStackRefEnum : public ISOSEnum
{
public:
	virtual HRESULT STDMETHODCALLTYPE Next(
		/* [in] */ unsigned int count,
		/* [length_is][size_is][out] */ SOSStackRefData ref[],
		/* [out] */ unsigned int *pFetched) = 0;

	virtual HRESULT STDMETHODCALLTYPE EnumerateErrors(
		/* [out] */ ISOSStackRefErrorEnum **ppEnum) = 0;

};

MIDL_INTERFACE("436f00f2-b42a-4b9f-870c-e73db66ae930")
ISOSDacInterface : public IUnknown
{
public:

	virtual HRESULT STDMETHODCALLTYPE GetThreadStoreData(
		struct DacpThreadStoreData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainStoreData(
		struct DacpAppDomainStoreData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainList(
		unsigned int count,
		CLRDATA_ADDRESS values[],
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainData(
		CLRDATA_ADDRESS addr,
		struct DacpAppDomainData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainName(
		CLRDATA_ADDRESS addr,
		unsigned int count,
		WCHAR *name,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDomainFromContext(
		CLRDATA_ADDRESS context,
		CLRDATA_ADDRESS *domain) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyList(
		CLRDATA_ADDRESS appDomain,
		int count,
		CLRDATA_ADDRESS values[],
		int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyData(
		CLRDATA_ADDRESS baseDomainPtr,
		CLRDATA_ADDRESS assembly,

		struct DacpAssemblyData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyName(
		CLRDATA_ADDRESS assembly,
		unsigned int count,
		WCHAR *name,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModule(
		CLRDATA_ADDRESS addr,
		IXCLRDataModule **mod) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetModuleData(
		CLRDATA_ADDRESS moduleAddr,
		struct DacpModuleData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE TraverseModuleMap(
		ModuleMapType mmt,
		CLRDATA_ADDRESS moduleAddr,
		MODULEMAPTRAVERSE pCallback,
		LPVOID token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyModuleList(
		CLRDATA_ADDRESS assembly,
		unsigned int count,
		CLRDATA_ADDRESS modules[],
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetILForModule(
		CLRDATA_ADDRESS moduleAddr,
		DWORD rva,
		CLRDATA_ADDRESS *il) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadData(
		CLRDATA_ADDRESS thread,
		struct DacpThreadData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadFromThinlockID(
		UINT thinLockId,
		CLRDATA_ADDRESS *pThread) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStackLimits(
		CLRDATA_ADDRESS threadPtr,
		CLRDATA_ADDRESS *lower,
		CLRDATA_ADDRESS *upper,
		CLRDATA_ADDRESS *fp) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescData(
		CLRDATA_ADDRESS methodDesc,
		CLRDATA_ADDRESS ip,
		struct DacpMethodDescData *data,
		ULONG cRevertedRejitVersions,
		struct DacpReJitData *rgRevertedRejitData,
		ULONG *pcNeededRevertedRejitData) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescPtrFromIP(
		CLRDATA_ADDRESS ip,
		CLRDATA_ADDRESS *ppMD) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescName(
		CLRDATA_ADDRESS methodDesc,
		unsigned int count,
		WCHAR *name,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescPtrFromFrame(
		CLRDATA_ADDRESS frameAddr,
		CLRDATA_ADDRESS *ppMD) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescFromToken(
		CLRDATA_ADDRESS moduleAddr,
		mdToken token,
		CLRDATA_ADDRESS *methodDesc) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodDescTransparencyData(
		CLRDATA_ADDRESS methodDesc,
		struct DacpMethodDescTransparencyData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeHeaderData(
		CLRDATA_ADDRESS ip,
		struct DacpCodeHeaderData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetJitManagerList(
		unsigned int count,
		struct DacpJitManagerInfo *managers,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetJitHelperFunctionName(
		CLRDATA_ADDRESS ip,
		unsigned int count,
		char *name,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetJumpThunkTarget(
		T_CONTEXT *ctx,
		CLRDATA_ADDRESS *targetIP,
		CLRDATA_ADDRESS *targetMD) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadpoolData(
		struct DacpThreadpoolData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetWorkRequestData(
		CLRDATA_ADDRESS addrWorkRequest,
		struct DacpWorkRequestData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHillClimbingLogEntry(
		CLRDATA_ADDRESS addr,
		struct DacpHillClimbingLogEntry *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectData(
		CLRDATA_ADDRESS objAddr,
		struct DacpObjectData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectStringData(
		CLRDATA_ADDRESS obj,
		unsigned int count,
		WCHAR *stringData,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetObjectClassName(
		CLRDATA_ADDRESS obj,
		unsigned int count,
		WCHAR *className,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableName(
		CLRDATA_ADDRESS mt,
		unsigned int count,
		WCHAR *mtName,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableData(
		CLRDATA_ADDRESS mt,
		struct DacpMethodTableData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableSlot(
		CLRDATA_ADDRESS mt,
		unsigned int slot,
		CLRDATA_ADDRESS *value) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableFieldData(
		CLRDATA_ADDRESS mt,
		struct DacpMethodTableFieldData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableTransparencyData(
		CLRDATA_ADDRESS mt,
		struct DacpMethodTableTransparencyData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodTableForEEClass(
		CLRDATA_ADDRESS eeClass,
		CLRDATA_ADDRESS *value) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFieldDescData(
		CLRDATA_ADDRESS fieldDesc,
		struct DacpFieldDescData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFrameName(
		CLRDATA_ADDRESS vtable,
		unsigned int count,
		WCHAR *frameName,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetPEFileBase(
		CLRDATA_ADDRESS addr,
		CLRDATA_ADDRESS *base) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetPEFileName(
		CLRDATA_ADDRESS addr,
		unsigned int count,
		WCHAR *fileName,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGCHeapData(
		struct DacpGcHeapData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGCHeapList(
		unsigned int count,
		CLRDATA_ADDRESS heaps[],
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGCHeapDetails(
		CLRDATA_ADDRESS heap,
		struct DacpGcHeapDetails *details) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGCHeapStaticData(
		struct DacpGcHeapDetails *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHeapSegmentData(
		CLRDATA_ADDRESS seg,
		struct DacpHeapSegmentData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetOOMData(
		CLRDATA_ADDRESS oomAddr,
		struct DacpOomData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetOOMStaticData(
		struct DacpOomData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHeapAnalyzeData(
		CLRDATA_ADDRESS addr,
		struct DacpGcHeapAnalyzeData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHeapAnalyzeStaticData(
		struct DacpGcHeapAnalyzeData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDomainLocalModuleData(
		CLRDATA_ADDRESS addr,
		struct DacpDomainLocalModuleData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDomainLocalModuleDataFromAppDomain(
		CLRDATA_ADDRESS appDomainAddr,
		int moduleID,
		struct DacpDomainLocalModuleData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDomainLocalModuleDataFromModule(
		CLRDATA_ADDRESS moduleAddr,
		struct DacpDomainLocalModuleData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadLocalModuleData(
		CLRDATA_ADDRESS thread,
		unsigned int index,
		struct DacpThreadLocalModuleData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSyncBlockData(
		unsigned int number,
		struct DacpSyncBlockData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSyncBlockCleanupData(
		CLRDATA_ADDRESS addr,
		struct DacpSyncBlockCleanupData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHandleEnum(
		ISOSHandleEnum **ppHandleEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHandleEnumForTypes(
		unsigned int types[],
		unsigned int count,
		ISOSHandleEnum **ppHandleEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHandleEnumForGC(
		unsigned int gen,
		ISOSHandleEnum **ppHandleEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE TraverseEHInfo(
		CLRDATA_ADDRESS ip,
		DUMPEHINFO pCallback,
		LPVOID token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNestedExceptionData(
		CLRDATA_ADDRESS exception,
		CLRDATA_ADDRESS *exceptionObject,
		CLRDATA_ADDRESS *nextNestedException) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStressLogAddress(
		CLRDATA_ADDRESS *stressLog) = 0;

	virtual HRESULT STDMETHODCALLTYPE TraverseLoaderHeap(
		CLRDATA_ADDRESS loaderHeapAddr,
		VISITHEAP pCallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCodeHeapList(
		CLRDATA_ADDRESS jitManager,
		unsigned int count,
		struct DacpJitCodeHeapInfo *codeHeaps,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE TraverseVirtCallStubHeap(
		CLRDATA_ADDRESS pAppDomain,
		VCSHeapType heaptype,
		VISITHEAP pCallback) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetUsefulGlobals(
		struct DacpUsefulGlobalsData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetClrWatsonBuckets(
		CLRDATA_ADDRESS thread,
		void *pGenericModeBlock) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetTLSIndex(
		ULONG *pIndex) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDacModuleHandle(
		HMODULE *phModule) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRCWData(
		CLRDATA_ADDRESS addr,
		struct DacpRCWData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRCWInterfaces(
		CLRDATA_ADDRESS rcw,
		unsigned int count,
		struct DacpCOMInterfacePointerData *interfaces,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCCWData(
		CLRDATA_ADDRESS ccw,
		struct DacpCCWData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetCCWInterfaces(
		CLRDATA_ADDRESS ccw,
		unsigned int count,
		struct DacpCOMInterfacePointerData *interfaces,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE TraverseRCWCleanupList(
		CLRDATA_ADDRESS cleanupListPtr,
		VISITRCWFORCLEANUP pCallback,
		LPVOID token) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStackReferences(
		/* [in] */ DWORD osThreadID,
		/* [out] */ ISOSStackRefEnum **ppEnum) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRegisterName(
		/* [in] */ int regName,
		/* [in] */ unsigned int count,
		/* [out] */ WCHAR *buffer,
		/* [out] */ unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetThreadAllocData(
		CLRDATA_ADDRESS thread,
		struct DacpAllocData *data) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetHeapAllocData(
		unsigned int count,
		struct DacpGenerationAllocData *data,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFailedAssemblyList(
		CLRDATA_ADDRESS appDomain,
		int count,
		CLRDATA_ADDRESS values[],
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetPrivateBinPaths(
		CLRDATA_ADDRESS appDomain,
		int count,
		WCHAR *paths,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAssemblyLocation(
		CLRDATA_ADDRESS assembly,
		int count,
		WCHAR *location,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAppDomainConfigFile(
		CLRDATA_ADDRESS appDomain,
		int count,
		WCHAR *configFile,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetApplicationBase(
		CLRDATA_ADDRESS appDomain,
		int count,
		WCHAR *base,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFailedAssemblyData(
		CLRDATA_ADDRESS assembly,
		unsigned int *pContext,
		HRESULT *pResult) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFailedAssemblyLocation(
		CLRDATA_ADDRESS assesmbly,
		unsigned int count,
		WCHAR *location,
		unsigned int *pNeeded) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetFailedAssemblyDisplayName(
		CLRDATA_ADDRESS assembly,
		unsigned int count,
		WCHAR *name,
		unsigned int *pNeeded) = 0;
};

struct DacpMethodDescData //: ZeroInit<DacpMethodDescData>
{
	BOOL            bHasNativeCode;
	BOOL            bIsDynamic;
	WORD            wSlotNumber;
	CLRDATA_ADDRESS NativeCodeAddr;
	// Useful for breaking when a method is jitted.
	CLRDATA_ADDRESS AddressOfNativeCodeSlot;

	CLRDATA_ADDRESS MethodDescPtr;
	CLRDATA_ADDRESS MethodTablePtr;
	CLRDATA_ADDRESS ModulePtr;

	mdToken                  MDToken;
	CLRDATA_ADDRESS GCInfo;
	CLRDATA_ADDRESS GCStressCodeCopy;

	// This is only valid if bIsDynamic is true
	CLRDATA_ADDRESS managedDynamicMethodObject;

	CLRDATA_ADDRESS requestedIP;

	// Gives info for the single currently active version of a method
	DacpReJitData       rejitDataCurrent;

	// Gives info corresponding to requestedIP (for !ip2md)
	DacpReJitData       rejitDataRequested;

	// Total number of rejit versions that have been jitted
	ULONG               cJittedRejitVersions;

	HRESULT Request(ISOSDacInterface *sos, CLRDATA_ADDRESS addr)
	{
		return sos->GetMethodDescData(
			addr,
			NULL,   // IP address
			this,
			0,      // cRejitData
			NULL,   // rejitData[]
			NULL    // pcNeededRejitData
		);
	}
};

typedef void *HCORENUM;

typedef mdToken mdModule;               // Module token (roughly, a scope)
typedef mdToken mdTypeRef;              // TypeRef reference (this or other scope)
typedef mdToken mdTypeDef;              // TypeDef in this scope
typedef mdToken mdFieldDef;             // Field in this scope
typedef mdToken mdMethodDef;            // Method in this scope
typedef mdToken mdParamDef;             // param token
typedef mdToken mdInterfaceImpl;        // interface implementation token

typedef mdToken mdMemberRef;            // MemberRef (this or other scope)
typedef mdToken mdCustomAttribute;      // attribute token
typedef mdToken mdPermission;           // DeclSecurity

typedef mdToken mdSignature;            // Signature object
typedef mdToken mdEvent;                // event token
typedef mdToken mdProperty;             // property token

typedef mdToken mdModuleRef;            // Module reference (for the imported modules)

typedef mdToken mdTypeSpec;             // TypeSpec object
typedef mdToken mdString;               // User literal string token.

typedef mdToken mdGenericParam;         // formal parameter to generic type or method
typedef mdToken mdMethodSpec;           // instantiation of a generic method
typedef mdToken mdGenericParamConstraint; // constraint on a formal generic parameter


typedef unsigned __int8 COR_SIGNATURE;

typedef COR_SIGNATURE* PCOR_SIGNATURE;      // pointer to a cor sig.  Not void* so that
											// the bytes can be incremented easily
typedef const COR_SIGNATURE* PCCOR_SIGNATURE;

typedef struct COR_FIELD_OFFSET
{
	mdFieldDef  ridOfField;
	ULONG       ulOffset;
} COR_FIELD_OFFSET;

typedef const char * MDUTF8CSTR;
typedef UNALIGNED void const *UVCP_CONSTANT;

typedef void* ISymUnmanagedDocument;
typedef void* ISymUnmanagedNamespace;
struct ISymUnmanagedScope;

MIDL_INTERFACE("9F60EEBE-2D9A-3F7C-BF58-80BC991C60BB")
ISymUnmanagedVariable : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetName(
		/* [in] */ ULONG32 cchName,
		/* [out] */ __RPC__out ULONG32 *pcchName,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cchName, *pcchName) WCHAR szName[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAttributes(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSignature(
		/* [in] */ ULONG32 cSig,
		/* [out] */ __RPC__out ULONG32 *pcSig,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cSig, *pcSig) BYTE sig[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressKind(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressField1(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressField2(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetAddressField3(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStartOffset(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetEndOffset(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

};

MIDL_INTERFACE("B62B923C-B500-3158-A543-24F307A8B7E1")
ISymUnmanagedMethod : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetToken(
		/* [retval][out] */ __RPC__out mdMethodDef *pToken) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSequencePointCount(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRootScope(
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedScope **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetScopeFromOffset(
		/* [in] */ ULONG32 offset,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedScope **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetOffset(
		/* [in] */ __RPC__in_opt ISymUnmanagedDocument *document,
		/* [in] */ ULONG32 line,
		/* [in] */ ULONG32 column,
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetRanges(
		/* [in] */ __RPC__in_opt ISymUnmanagedDocument *document,
		/* [in] */ ULONG32 line,
		/* [in] */ ULONG32 column,
		/* [in] */ ULONG32 cRanges,
		/* [out] */ __RPC__out ULONG32 *pcRanges,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cRanges, *pcRanges) ULONG32 ranges[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetParameters(
		/* [in] */ ULONG32 cParams,
		/* [out] */ __RPC__out ULONG32 *pcParams,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cParams, *pcParams) ISymUnmanagedVariable *params[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNamespace(
		/* [out] */ __RPC__deref_out_opt ISymUnmanagedNamespace **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSourceStartEnd(
		/* [in] */ __RPC__in_ecount_full(2) ISymUnmanagedDocument *docs[2],
		/* [in] */ __RPC__in_ecount_full(2) ULONG32 lines[2],
		/* [in] */ __RPC__in_ecount_full(2) ULONG32 columns[2],
		/* [out] */ __RPC__out BOOL *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSequencePoints(
		/* [in] */ ULONG32 cPoints,
		/* [out] */ __RPC__out ULONG32 *pcPoints,
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ULONG32 offsets[],
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ISymUnmanagedDocument *documents[],
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ULONG32 lines[],
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ULONG32 columns[],
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ULONG32 endLines[],
		/* [size_is][in] */ __RPC__in_ecount_full(cPoints) ULONG32 endColumns[]) = 0;

};

MIDL_INTERFACE("68005D0F-B8E0-3B01-84D5-A11A94154942")
ISymUnmanagedScope : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetMethod(
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedMethod **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetParent(
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedScope **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetChildren(
		/* [in] */ ULONG32 cChildren,
		/* [out] */ __RPC__out ULONG32 *pcChildren,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cChildren, *pcChildren) ISymUnmanagedScope *children[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetStartOffset(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetEndOffset(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLocalCount(
		/* [retval][out] */ __RPC__out ULONG32 *pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetLocals(
		/* [in] */ ULONG32 cLocals,
		/* [out] */ __RPC__out ULONG32 *pcLocals,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cLocals, *pcLocals) ISymUnmanagedVariable *locals[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNamespaces(
		/* [in] */ ULONG32 cNameSpaces,
		/* [out] */ __RPC__out ULONG32 *pcNameSpaces,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cNameSpaces, *pcNameSpaces) ISymUnmanagedNamespace *namespaces[]) = 0;

};

EXTERN_GUID(IID_IMetaDataImport, 0x7dac8207, 0xd3ae, 0x4c75, 0x9b, 0x67, 0x92, 0x80, 0x1a, 0x49, 0x7d, 0x44);

#undef  INTERFACE
#define INTERFACE IMetaDataImport
DECLARE_INTERFACE_(IMetaDataImport, IUnknown)
{
	STDMETHOD_(void, CloseEnum)(HCORENUM hEnum) PURE;
	STDMETHOD(CountEnum)(HCORENUM hEnum, ULONG *pulCount) PURE;
	STDMETHOD(ResetEnum)(HCORENUM hEnum, ULONG ulPos) PURE;
	STDMETHOD(EnumTypeDefs)(HCORENUM *phEnum, mdTypeDef rTypeDefs[],
		ULONG cMax, ULONG *pcTypeDefs) PURE;
	STDMETHOD(EnumInterfaceImpls)(HCORENUM *phEnum, mdTypeDef td,
		mdInterfaceImpl rImpls[], ULONG cMax,
		ULONG* pcImpls) PURE;
	STDMETHOD(EnumTypeRefs)(HCORENUM *phEnum, mdTypeRef rTypeRefs[],
		ULONG cMax, ULONG* pcTypeRefs) PURE;

	STDMETHOD(FindTypeDefByName)(           // S_OK or error.
		LPCWSTR     szTypeDef,              // [IN] Name of the Type.
		mdToken     tkEnclosingClass,       // [IN] TypeDef/TypeRef for Enclosing class.
		mdTypeDef   *ptd) PURE;             // [OUT] Put the TypeDef token here.

	STDMETHOD(GetScopeProps)(               // S_OK or error.
		_Out_writes_to_opt_(cchName, *pchName)
		LPWSTR      szName,                 // [OUT] Put the name here.
		ULONG       cchName,                // [IN] Size of name buffer in wide chars.
		ULONG       *pchName,               // [OUT] Put size of name (wide chars) here.
		GUID        *pmvid) PURE;           // [OUT, OPTIONAL] Put MVID here.

	STDMETHOD(GetModuleFromScope)(          // S_OK.
		mdModule    *pmd) PURE;             // [OUT] Put mdModule token here.

	STDMETHOD(GetTypeDefProps)(             // S_OK or error.
		mdTypeDef   td,                     // [IN] TypeDef token for inquiry.
		_Out_writes_to_opt_(cchTypeDef, *pchTypeDef)
		LPWSTR      szTypeDef,              // [OUT] Put name here.
		ULONG       cchTypeDef,             // [IN] size of name buffer in wide chars.
		ULONG       *pchTypeDef,            // [OUT] put size of name (wide chars) here.
		DWORD       *pdwTypeDefFlags,       // [OUT] Put flags here.
		mdToken     *ptkExtends) PURE;      // [OUT] Put base class TypeDef/TypeRef here.

	STDMETHOD(GetInterfaceImplProps)(       // S_OK or error.
		mdInterfaceImpl iiImpl,             // [IN] InterfaceImpl token.
		mdTypeDef   *pClass,                // [OUT] Put implementing class token here.
		mdToken     *ptkIface) PURE;        // [OUT] Put implemented interface token here.

	STDMETHOD(GetTypeRefProps)(             // S_OK or error.
		mdTypeRef   tr,                     // [IN] TypeRef token.
		mdToken     *ptkResolutionScope,    // [OUT] Resolution scope, ModuleRef or AssemblyRef.
		_Out_writes_to_opt_(cchName, *pchName)
		LPWSTR      szName,                 // [OUT] Name of the TypeRef.
		ULONG       cchName,                // [IN] Size of buffer.
		ULONG       *pchName) PURE;         // [OUT] Size of Name.

	STDMETHOD(ResolveTypeRef)(mdTypeRef tr, REFIID riid, IUnknown **ppIScope, mdTypeDef *ptd) PURE;

	STDMETHOD(EnumMembers)(                 // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		mdToken     rMembers[],             // [OUT] Put MemberDefs here.
		ULONG       cMax,                   // [IN] Max MemberDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumMembersWithName)(         // S_OK, S_FALSE, or error.
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		LPCWSTR     szName,                 // [IN] Limit results to those with this name.
		mdToken     rMembers[],             // [OUT] Put MemberDefs here.
		ULONG       cMax,                   // [IN] Max MemberDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumMethods)(                 // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		mdMethodDef rMethods[],             // [OUT] Put MethodDefs here.
		ULONG       cMax,                   // [IN] Max MethodDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumMethodsWithName)(         // S_OK, S_FALSE, or error.
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		LPCWSTR     szName,                 // [IN] Limit results to those with this name.
		mdMethodDef rMethods[],             // [OU] Put MethodDefs here.
		ULONG       cMax,                   // [IN] Max MethodDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumFields)(                  // S_OK, S_FALSE, or error.
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		mdFieldDef  rFields[],              // [OUT] Put FieldDefs here.
		ULONG       cMax,                   // [IN] Max FieldDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumFieldsWithName)(          // S_OK, S_FALSE, or error.
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   cl,                     // [IN] TypeDef to scope the enumeration.
		LPCWSTR     szName,                 // [IN] Limit results to those with this name.
		mdFieldDef  rFields[],              // [OUT] Put MemberDefs here.
		ULONG       cMax,                   // [IN] Max MemberDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.


	STDMETHOD(EnumParams)(                  // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdMethodDef mb,                     // [IN] MethodDef to scope the enumeration. 
		mdParamDef  rParams[],              // [OUT] Put ParamDefs here.
		ULONG       cMax,                   // [IN] Max ParamDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumMemberRefs)(              // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdToken     tkParent,               // [IN] Parent token to scope the enumeration.
		mdMemberRef rMemberRefs[],          // [OUT] Put MemberRefs here.
		ULONG       cMax,                   // [IN] Max MemberRefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumMethodImpls)(             // S_OK, S_FALSE, or error
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   td,                     // [IN] TypeDef to scope the enumeration.
		mdToken     rMethodBody[],          // [OUT] Put Method Body tokens here.
		mdToken     rMethodDecl[],          // [OUT] Put Method Declaration tokens here.
		ULONG       cMax,                   // [IN] Max tokens to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(EnumPermissionSets)(          // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdToken     tk,                     // [IN] if !NIL, token to scope the enumeration.
		DWORD       dwActions,              // [IN] if !0, return only these actions.
		mdPermission rPermission[],         // [OUT] Put Permissions here.
		ULONG       cMax,                   // [IN] Max Permissions to put. 
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(FindMember)(
		mdTypeDef   td,                     // [IN] given typedef
		LPCWSTR     szName,                 // [IN] member name 
		PCCOR_SIGNATURE pvSigBlob,          // [IN] point to a blob value of CLR signature 
		ULONG       cbSigBlob,              // [IN] count of bytes in the signature blob
		mdToken     *pmb) PURE;             // [OUT] matching memberdef 

	STDMETHOD(FindMethod)(
		mdTypeDef   td,                     // [IN] given typedef
		LPCWSTR     szName,                 // [IN] member name 
		PCCOR_SIGNATURE pvSigBlob,          // [IN] point to a blob value of CLR signature 
		ULONG       cbSigBlob,              // [IN] count of bytes in the signature blob
		mdMethodDef *pmb) PURE;             // [OUT] matching memberdef 

	STDMETHOD(FindField)(
		mdTypeDef   td,                     // [IN] given typedef
		LPCWSTR     szName,                 // [IN] member name 
		PCCOR_SIGNATURE pvSigBlob,          // [IN] point to a blob value of CLR signature 
		ULONG       cbSigBlob,              // [IN] count of bytes in the signature blob
		mdFieldDef  *pmb) PURE;             // [OUT] matching memberdef 

	STDMETHOD(FindMemberRef)(
		mdTypeRef   td,                     // [IN] given typeRef
		LPCWSTR     szName,                 // [IN] member name 
		PCCOR_SIGNATURE pvSigBlob,          // [IN] point to a blob value of CLR signature 
		ULONG       cbSigBlob,              // [IN] count of bytes in the signature blob
		mdMemberRef *pmr) PURE;             // [OUT] matching memberref 

	STDMETHOD(GetMethodProps)(
		mdMethodDef mb,                     // The method for which to get props.
		mdTypeDef   *pClass,                // Put method's class here. 
		_Out_writes_to_opt_(cchMethod, *pchMethod)
		LPWSTR      szMethod,               // Put method's name here.
		ULONG       cchMethod,              // Size of szMethod buffer in wide chars.
		ULONG       *pchMethod,             // Put actual size here 
		DWORD       *pdwAttr,               // Put flags here.
		PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to the blob value of meta data
		ULONG       *pcbSigBlob,            // [OUT] actual size of signature blob
		ULONG       *pulCodeRVA,            // [OUT] codeRVA
		DWORD       *pdwImplFlags) PURE;    // [OUT] Impl. Flags

	STDMETHOD(GetMemberRefProps)(           // S_OK or error.
		mdMemberRef mr,                     // [IN] given memberref 
		mdToken     *ptk,                   // [OUT] Put classref or classdef here. 
		_Out_writes_to_opt_(cchMember, *pchMember)
		LPWSTR      szMember,               // [OUT] buffer to fill for member's name
		ULONG       cchMember,              // [IN] the count of char of szMember
		ULONG       *pchMember,             // [OUT] actual count of char in member name
		PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to meta data blob value
		ULONG       *pbSig) PURE;           // [OUT] actual size of signature blob

	STDMETHOD(EnumProperties)(              // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   td,                     // [IN] TypeDef to scope the enumeration.
		mdProperty  rProperties[],          // [OUT] Put Properties here.
		ULONG       cMax,                   // [IN] Max properties to put.
		ULONG       *pcProperties) PURE;    // [OUT] Put # put here.

	STDMETHOD(EnumEvents)(                  // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdTypeDef   td,                     // [IN] TypeDef to scope the enumeration.
		mdEvent     rEvents[],              // [OUT] Put events here.
		ULONG       cMax,                   // [IN] Max events to put.
		ULONG       *pcEvents) PURE;        // [OUT] Put # put here.

	STDMETHOD(GetEventProps)(               // S_OK, S_FALSE, or error. 
		mdEvent     ev,                     // [IN] event token 
		mdTypeDef   *pClass,                // [OUT] typedef containing the event declarion.
		LPCWSTR     szEvent,                // [OUT] Event name 
		ULONG       cchEvent,               // [IN] the count of wchar of szEvent
		ULONG       *pchEvent,              // [OUT] actual count of wchar for event's name 
		DWORD       *pdwEventFlags,         // [OUT] Event flags.
		mdToken     *ptkEventType,          // [OUT] EventType class
		mdMethodDef *pmdAddOn,              // [OUT] AddOn method of the event
		mdMethodDef *pmdRemoveOn,           // [OUT] RemoveOn method of the event
		mdMethodDef *pmdFire,               // [OUT] Fire method of the event
		mdMethodDef rmdOtherMethod[],       // [OUT] other method of the event
		ULONG       cMax,                   // [IN] size of rmdOtherMethod
		ULONG       *pcOtherMethod) PURE;   // [OUT] total number of other method of this event 

	STDMETHOD(EnumMethodSemantics)(         // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdMethodDef mb,                     // [IN] MethodDef to scope the enumeration. 
		mdToken     rEventProp[],           // [OUT] Put Event/Property here.
		ULONG       cMax,                   // [IN] Max properties to put.
		ULONG       *pcEventProp) PURE;     // [OUT] Put # put here.

	STDMETHOD(GetMethodSemantics)(          // S_OK, S_FALSE, or error. 
		mdMethodDef mb,                     // [IN] method token
		mdToken     tkEventProp,            // [IN] event/property token.
		DWORD       *pdwSemanticsFlags) PURE; // [OUT] the role flags for the method/propevent pair 

	STDMETHOD(GetClassLayout) (
		mdTypeDef   td,                     // [IN] give typedef
		DWORD       *pdwPackSize,           // [OUT] 1, 2, 4, 8, or 16
		COR_FIELD_OFFSET rFieldOffset[],    // [OUT] field offset array 
		ULONG       cMax,                   // [IN] size of the array
		ULONG       *pcFieldOffset,         // [OUT] needed array size
		ULONG       *pulClassSize) PURE;        // [OUT] the size of the class

	STDMETHOD(GetFieldMarshal) (
		mdToken     tk,                     // [IN] given a field's memberdef
		PCCOR_SIGNATURE *ppvNativeType,     // [OUT] native type of this field
		ULONG       *pcbNativeType) PURE;   // [OUT] the count of bytes of *ppvNativeType

	STDMETHOD(GetRVA)(                      // S_OK or error.
		mdToken     tk,                     // Member for which to set offset
		ULONG       *pulCodeRVA,            // The offset
		DWORD       *pdwImplFlags) PURE;    // the implementation flags 

	STDMETHOD(GetPermissionSetProps) (
		mdPermission pm,                    // [IN] the permission token.
		DWORD       *pdwAction,             // [OUT] CorDeclSecurity.
		void const  **ppvPermission,        // [OUT] permission blob.
		ULONG       *pcbPermission) PURE;   // [OUT] count of bytes of pvPermission.

	STDMETHOD(GetSigFromToken)(             // S_OK or error.
		mdSignature mdSig,                  // [IN] Signature token.
		PCCOR_SIGNATURE *ppvSig,            // [OUT] return pointer to token.
		ULONG       *pcbSig) PURE;          // [OUT] return size of signature.

	STDMETHOD(GetModuleRefProps)(           // S_OK or error.
		mdModuleRef mur,                    // [IN] moduleref token.
		_Out_writes_to_opt_(cchName, *pchName)
		LPWSTR      szName,                 // [OUT] buffer to fill with the moduleref name.
		ULONG       cchName,                // [IN] size of szName in wide characters.
		ULONG       *pchName) PURE;         // [OUT] actual count of characters in the name.

	STDMETHOD(EnumModuleRefs)(              // S_OK or error.
		HCORENUM    *phEnum,                // [IN|OUT] pointer to the enum.
		mdModuleRef rModuleRefs[],          // [OUT] put modulerefs here.
		ULONG       cmax,                   // [IN] max memberrefs to put.
		ULONG       *pcModuleRefs) PURE;    // [OUT] put # put here.

	STDMETHOD(GetTypeSpecFromToken)(        // S_OK or error.
		mdTypeSpec typespec,                // [IN] TypeSpec token.
		PCCOR_SIGNATURE *ppvSig,            // [OUT] return pointer to TypeSpec signature
		ULONG       *pcbSig) PURE;          // [OUT] return size of signature.

	STDMETHOD(GetNameFromToken)(            // Not Recommended! May be removed!
		mdToken     tk,                     // [IN] Token to get name from.  Must have a name.
		MDUTF8CSTR  *pszUtf8NamePtr) PURE;  // [OUT] Return pointer to UTF8 name in heap.

	STDMETHOD(EnumUnresolvedMethods)(       // S_OK, S_FALSE, or error. 
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdToken     rMethods[],             // [OUT] Put MemberDefs here.
		ULONG       cMax,                   // [IN] Max MemberDefs to put.
		ULONG       *pcTokens) PURE;        // [OUT] Put # put here.

	STDMETHOD(GetUserString)(               // S_OK or error.
		mdString    stk,                    // [IN] String token.
		_Out_writes_to_opt_(cchString, *pchString)
		LPWSTR      szString,               // [OUT] Copy of string.
		ULONG       cchString,              // [IN] Max chars of room in szString.
		ULONG       *pchString) PURE;       // [OUT] How many chars in actual string.

	STDMETHOD(GetPinvokeMap)(               // S_OK or error.
		mdToken     tk,                     // [IN] FieldDef or MethodDef.
		DWORD       *pdwMappingFlags,       // [OUT] Flags used for mapping.
		_Out_writes_to_opt_(cchImportName, *pchImportName)
		LPWSTR      szImportName,           // [OUT] Import name.
		ULONG       cchImportName,          // [IN] Size of the name buffer.
		ULONG       *pchImportName,         // [OUT] Actual number of characters stored.
		mdModuleRef *pmrImportDLL) PURE;    // [OUT] ModuleRef token for the target DLL.

	STDMETHOD(EnumSignatures)(              // S_OK or error.
		HCORENUM    *phEnum,                // [IN|OUT] pointer to the enum.
		mdSignature rSignatures[],          // [OUT] put signatures here.
		ULONG       cmax,                   // [IN] max signatures to put.
		ULONG       *pcSignatures) PURE;    // [OUT] put # put here.

	STDMETHOD(EnumTypeSpecs)(               // S_OK or error.
		HCORENUM    *phEnum,                // [IN|OUT] pointer to the enum.
		mdTypeSpec  rTypeSpecs[],           // [OUT] put TypeSpecs here.
		ULONG       cmax,                   // [IN] max TypeSpecs to put.
		ULONG       *pcTypeSpecs) PURE;     // [OUT] put # put here.

	STDMETHOD(EnumUserStrings)(             // S_OK or error.
		HCORENUM    *phEnum,                // [IN/OUT] pointer to the enum.
		mdString    rStrings[],             // [OUT] put Strings here.
		ULONG       cmax,                   // [IN] max Strings to put.
		ULONG       *pcStrings) PURE;       // [OUT] put # put here.

	STDMETHOD(GetParamForMethodIndex)(      // S_OK or error.
		mdMethodDef md,                     // [IN] Method token.
		ULONG       ulParamSeq,             // [IN] Parameter sequence.
		mdParamDef  *ppd) PURE;             // [IN] Put Param token here.

	STDMETHOD(EnumCustomAttributes)(        // S_OK or error.
		HCORENUM    *phEnum,                // [IN, OUT] COR enumerator.
		mdToken     tk,                     // [IN] Token to scope the enumeration, 0 for all.
		mdToken     tkType,                 // [IN] Type of interest, 0 for all.
		mdCustomAttribute rCustomAttributes[], // [OUT] Put custom attribute tokens here.
		ULONG       cMax,                   // [IN] Size of rCustomAttributes.
		ULONG       *pcCustomAttributes) PURE;  // [OUT, OPTIONAL] Put count of token values here.

	STDMETHOD(GetCustomAttributeProps)(     // S_OK or error.
		mdCustomAttribute cv,               // [IN] CustomAttribute token.
		mdToken     *ptkObj,                // [OUT, OPTIONAL] Put object token here.
		mdToken     *ptkType,               // [OUT, OPTIONAL] Put AttrType token here.
		void const  **ppBlob,               // [OUT, OPTIONAL] Put pointer to data here.
		ULONG       *pcbSize) PURE;         // [OUT, OPTIONAL] Put size of date here.

	STDMETHOD(FindTypeRef)(
		mdToken     tkResolutionScope,      // [IN] ModuleRef, AssemblyRef or TypeRef.
		LPCWSTR     szName,                 // [IN] TypeRef Name.
		mdTypeRef   *ptr) PURE;             // [OUT] matching TypeRef.

	STDMETHOD(GetMemberProps)(
		mdToken     mb,                     // The member for which to get props.
		mdTypeDef   *pClass,                // Put member's class here. 
		_Out_writes_to_opt_(cchMember, *pchMember)
		LPWSTR      szMember,               // Put member's name here.
		ULONG       cchMember,              // Size of szMember buffer in wide chars.
		ULONG       *pchMember,             // Put actual size here 
		DWORD       *pdwAttr,               // Put flags here.
		PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to the blob value of meta data
		ULONG       *pcbSigBlob,            // [OUT] actual size of signature blob
		ULONG       *pulCodeRVA,            // [OUT] codeRVA
		DWORD       *pdwImplFlags,          // [OUT] Impl. Flags
		DWORD       *pdwCPlusTypeFlag,      // [OUT] flag for value type. selected ELEMENT_TYPE_*
		UVCP_CONSTANT *ppValue,             // [OUT] constant value 
		ULONG       *pcchValue) PURE;       // [OUT] size of constant string in chars, 0 for non-strings.

	STDMETHOD(GetFieldProps)(
		mdFieldDef  mb,                     // The field for which to get props.
		mdTypeDef   *pClass,                // Put field's class here.
		_Out_writes_to_opt_(cchField, *pchField)
		LPWSTR      szField,                // Put field's name here.
		ULONG       cchField,               // Size of szField buffer in wide chars.
		ULONG       *pchField,              // Put actual size here 
		DWORD       *pdwAttr,               // Put flags here.
		PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to the blob value of meta data
		ULONG       *pcbSigBlob,            // [OUT] actual size of signature blob
		DWORD       *pdwCPlusTypeFlag,      // [OUT] flag for value type. selected ELEMENT_TYPE_*
		UVCP_CONSTANT *ppValue,             // [OUT] constant value 
		ULONG       *pcchValue) PURE;       // [OUT] size of constant string in chars, 0 for non-strings.

	STDMETHOD(GetPropertyProps)(            // S_OK, S_FALSE, or error. 
		mdProperty  prop,                   // [IN] property token
		mdTypeDef   *pClass,                // [OUT] typedef containing the property declarion. 
		LPCWSTR     szProperty,             // [OUT] Property name
		ULONG       cchProperty,            // [IN] the count of wchar of szProperty
		ULONG       *pchProperty,           // [OUT] actual count of wchar for property name
		DWORD       *pdwPropFlags,          // [OUT] property flags.
		PCCOR_SIGNATURE *ppvSig,            // [OUT] property type. pointing to meta data internal blob 
		ULONG       *pbSig,                 // [OUT] count of bytes in *ppvSig
		DWORD       *pdwCPlusTypeFlag,      // [OUT] flag for value type. selected ELEMENT_TYPE_*
		UVCP_CONSTANT *ppDefaultValue,      // [OUT] constant value 
		ULONG       *pcchDefaultValue,      // [OUT] size of constant string in chars, 0 for non-strings.
		mdMethodDef *pmdSetter,             // [OUT] setter method of the property
		mdMethodDef *pmdGetter,             // [OUT] getter method of the property
		mdMethodDef rmdOtherMethod[],       // [OUT] other method of the property
		ULONG       cMax,                   // [IN] size of rmdOtherMethod
		ULONG       *pcOtherMethod) PURE;   // [OUT] total number of other method of this property

	STDMETHOD(GetParamProps)(               // S_OK or error.
		mdParamDef  tk,                     // [IN]The Parameter.
		mdMethodDef *pmd,                   // [OUT] Parent Method token.
		ULONG       *pulSequence,           // [OUT] Parameter sequence.
		_Out_writes_to_opt_(cchName, *pchName)
		LPWSTR      szName,                 // [OUT] Put name here.
		ULONG       cchName,                // [OUT] Size of name buffer.
		ULONG       *pchName,               // [OUT] Put actual size of name here.
		DWORD       *pdwAttr,               // [OUT] Put flags here.
		DWORD       *pdwCPlusTypeFlag,      // [OUT] Flag for value type. selected ELEMENT_TYPE_*.
		UVCP_CONSTANT *ppValue,             // [OUT] Constant value.
		ULONG       *pcchValue) PURE;       // [OUT] size of constant string in chars, 0 for non-strings.

	STDMETHOD(GetCustomAttributeByName)(    // S_OK or error.
		mdToken     tkObj,                  // [IN] Object with Custom Attribute.
		LPCWSTR     szName,                 // [IN] Name of desired Custom Attribute.
		const void  **ppData,               // [OUT] Put pointer to data here.
		ULONG       *pcbData) PURE;         // [OUT] Put size of data here.

	STDMETHOD_(BOOL, IsValidToken)(         // True or False.
		mdToken     tk) PURE;               // [IN] Given token.

	STDMETHOD(GetNestedClassProps)(         // S_OK or error.
		mdTypeDef   tdNestedClass,          // [IN] NestedClass token.
		mdTypeDef   *ptdEnclosingClass) PURE; // [OUT] EnclosingClass token.

	STDMETHOD(GetNativeCallConvFromSig)(    // S_OK or error.
		void const  *pvSig,                 // [IN] Pointer to signature.
		ULONG       cbSig,                  // [IN] Count of signature bytes.
		ULONG       *pCallConv) PURE;       // [OUT] Put calling conv here (see CorPinvokemap).

	STDMETHOD(IsGlobal)(                    // S_OK or error.
		mdToken     pd,                     // [IN] Type, Field, or Method token.
		int         *pbGlobal) PURE;        // [OUT] Put 1 if global, 0 otherwise.

											// This interface is sealed.  Do not change, add, or remove anything.  Instead, derive a new iterface.

};      // IMetaDataImport

EXTERN_GUID(IID_IMetaDataImport2, 0xfce5efa0, 0x8bba, 0x4f8e, 0xa0, 0x36, 0x8f, 0x20, 0x22, 0xb0, 0x84, 0x66);

//---
#undef  INTERFACE
#define INTERFACE IMetaDataImport2
DECLARE_INTERFACE_(IMetaDataImport2, IMetaDataImport)
{
	STDMETHOD(EnumGenericParams)(
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdToken      tk,                    // [IN] TypeDef or MethodDef whose generic parameters are requested
		mdGenericParam rGenericParams[],    // [OUT] Put GenericParams here.
		ULONG       cMax,                   // [IN] Max GenericParams to put.
		ULONG       *pcGenericParams) PURE; // [OUT] Put # put here.

	STDMETHOD(GetGenericParamProps)(        // S_OK or error.
		mdGenericParam gp,                  // [IN] GenericParam
		ULONG        *pulParamSeq,          // [OUT] Index of the type parameter
		DWORD        *pdwParamFlags,        // [OUT] Flags, for future use (e.g. variance)
		mdToken      *ptOwner,              // [OUT] Owner (TypeDef or MethodDef)
		DWORD       *reserved,              // [OUT] For future use (e.g. non-type parameters)
		_Out_writes_to_opt_(cchName, *pchName)
		LPWSTR       wzname,                // [OUT] Put name here
		ULONG        cchName,               // [IN] Size of buffer
		ULONG        *pchName) PURE;        // [OUT] Put size of name (wide chars) here.

	STDMETHOD(GetMethodSpecProps)(
		mdMethodSpec mi,                    // [IN] The method instantiation
		mdToken *tkParent,                  // [OUT] MethodDef or MemberRef
		PCCOR_SIGNATURE *ppvSigBlob,        // [OUT] point to the blob value of meta data
		ULONG       *pcbSigBlob) PURE;      // [OUT] actual size of signature blob

	STDMETHOD(EnumGenericParamConstraints)(
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdGenericParam tk,                  // [IN] GenericParam whose constraints are requested
		mdGenericParamConstraint rGenericParamConstraints[],    // [OUT] Put GenericParamConstraints here.
		ULONG       cMax,                   // [IN] Max GenericParamConstraints to put.
		ULONG       *pcGenericParamConstraints) PURE; // [OUT] Put # put here.

	STDMETHOD(GetGenericParamConstraintProps)( // S_OK or error.
		mdGenericParamConstraint gpc,       // [IN] GenericParamConstraint
		mdGenericParam *ptGenericParam,     // [OUT] GenericParam that is constrained
		mdToken      *ptkConstraintType) PURE; // [OUT] TypeDef/Ref/Spec constraint

	STDMETHOD(GetPEKind)(                   // S_OK or error.
		DWORD* pdwPEKind,                   // [OUT] The kind of PE (0 - not a PE)
		DWORD* pdwMAchine) PURE;            // [OUT] Machine as defined in NT header

	STDMETHOD(GetVersionString)(            // S_OK or error.
		_Out_writes_to_opt_(ccBufSize, *pccBufSize)
		LPWSTR      pwzBuf,                 // [OUT] Put version string here.
		DWORD       ccBufSize,              // [IN] size of the buffer, in wide chars
		DWORD       *pccBufSize) PURE;      // [OUT] Size of the version string, wide chars, including terminating nul.

	STDMETHOD(EnumMethodSpecs)(
		HCORENUM    *phEnum,                // [IN|OUT] Pointer to the enum.
		mdToken      tk,                    // [IN] MethodDef or MemberRef whose MethodSpecs are requested
		mdMethodSpec rMethodSpecs[],        // [OUT] Put MethodSpecs here.
		ULONG       cMax,                   // [IN] Max tokens to put.
		ULONG       *pcMethodSpecs) PURE;   // [OUT] Put actual count here.

}; // IMetaDataImport2

MIDL_INTERFACE("B4CE6286-2A6B-3712-A3B7-1EE1DAD467B5")
ISymUnmanagedReader : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetDocument(
		/* [in] */ __RPC__in WCHAR *url,
		/* [in] */ GUID language,
		/* [in] */ GUID languageVendor,
		/* [in] */ GUID documentType,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedDocument **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDocuments(
		/* [in] */ ULONG32 cDocs,
		/* [out] */ __RPC__out ULONG32 *pcDocs,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cDocs, *pcDocs) ISymUnmanagedDocument *pDocs[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetUserEntryPoint(
		/* [retval][out] */ __RPC__out mdMethodDef *pToken) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethod(
		/* [in] */ mdMethodDef token,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedMethod **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodByVersion(
		/* [in] */ mdMethodDef token,
		/* [in] */ int version,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedMethod **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetVariables(
		/* [in] */ mdToken parent,
		/* [in] */ ULONG32 cVars,
		/* [out] */ __RPC__out ULONG32 *pcVars,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cVars, *pcVars) ISymUnmanagedVariable *pVars[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetGlobalVariables(
		/* [in] */ ULONG32 cVars,
		/* [out] */ __RPC__out ULONG32 *pcVars,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cVars, *pcVars) ISymUnmanagedVariable *pVars[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodFromDocumentPosition(
		/* [in] */ __RPC__in_opt ISymUnmanagedDocument *document,
		/* [in] */ ULONG32 line,
		/* [in] */ ULONG32 column,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedMethod **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSymAttribute(
		/* [in] */ mdToken parent,
		/* [in] */ __RPC__in WCHAR *name,
		/* [in] */ ULONG32 cBuffer,
		/* [out] */ __RPC__out ULONG32 *pcBuffer,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cBuffer, *pcBuffer) BYTE buffer[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetNamespaces(
		/* [in] */ ULONG32 cNameSpaces,
		/* [out] */ __RPC__out ULONG32 *pcNameSpaces,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cNameSpaces, *pcNameSpaces) ISymUnmanagedNamespace *namespaces[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE Initialize(
		/* [in] */ __RPC__in_opt IUnknown *importer,
		/* [in] */ __RPC__in const WCHAR *filename,
		/* [in] */ __RPC__in const WCHAR *searchPath,
		/* [in] */ __RPC__in_opt IStream *pIStream) = 0;

	virtual HRESULT STDMETHODCALLTYPE UpdateSymbolStore(
		/* [in] */ __RPC__in const WCHAR *filename,
		/* [in] */ __RPC__in_opt IStream *pIStream) = 0;

	virtual HRESULT STDMETHODCALLTYPE ReplaceSymbolStore(
		/* [in] */ __RPC__in const WCHAR *filename,
		/* [in] */ __RPC__in_opt IStream *pIStream) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetSymbolStoreFileName(
		/* [in] */ ULONG32 cchName,
		/* [out] */ __RPC__out ULONG32 *pcchName,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cchName, *pcchName) WCHAR szName[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodsFromDocumentPosition(
		/* [in] */ __RPC__in_opt ISymUnmanagedDocument *document,
		/* [in] */ ULONG32 line,
		/* [in] */ ULONG32 column,
		/* [in] */ ULONG32 cMethod,
		/* [out] */ __RPC__out ULONG32 *pcMethod,
		/* [length_is][size_is][out] */ __RPC__out_ecount_part(cMethod, *pcMethod) ISymUnmanagedMethod *pRetVal[]) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetDocumentVersion(
		/* [in] */ __RPC__in_opt ISymUnmanagedDocument *pDoc,
		/* [out] */ __RPC__out int *version,
		/* [out] */ __RPC__out BOOL *pbCurrent) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetMethodVersion(
		/* [in] */ __RPC__in_opt ISymUnmanagedMethod *pMethod,
		/* [out] */ __RPC__out int *version) = 0;

};

MIDL_INTERFACE("AA544D42-28CB-11d3-BD22-0000F80849BD")
ISymUnmanagedBinder : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetReaderForFile(
		/* [in] */ __RPC__in_opt IUnknown *importer,
		/* [in] */ __RPC__in const WCHAR *fileName,
		/* [in] */ __RPC__in const WCHAR *searchPath,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedReader **pRetVal) = 0;

	virtual HRESULT STDMETHODCALLTYPE GetReaderFromStream(
		/* [in] */ __RPC__in_opt IUnknown *importer,
		/* [in] */ __RPC__in_opt IStream *pstream,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedReader **pRetVal) = 0;

};

MIDL_INTERFACE("ACCEE350-89AF-4ccb-8B40-1C2C4C6F9434")
ISymUnmanagedBinder2 : public ISymUnmanagedBinder
{
public:
	virtual HRESULT STDMETHODCALLTYPE GetReaderForFile2(
		/* [in] */ __RPC__in_opt IUnknown *importer,
		/* [in] */ __RPC__in const WCHAR *fileName,
		/* [in] */ __RPC__in const WCHAR *searchPath,
		/* [in] */ ULONG32 searchPolicy,
		/* [retval][out] */ __RPC__deref_out_opt ISymUnmanagedReader **pRetVal) = 0;

};

class DECLSPEC_UUID("0A29FF9E-7F9C-4437-8B11-F424491E3931")
	CorSymBinder_SxS;
