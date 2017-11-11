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
