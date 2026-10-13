#include <xenoblade/RVL_SDK/include/revolution/NWC24.h>
#include <xenoblade/RVL_SDK/include/revolution/OS.h>
#include <xenoblade/RVL_SDK/include/revolution/IPC.h>
#include <xenoblade/RVL_SDK/include/revolution/SC.h>


static OSShutdownFunctionInfo ShutdownFuncInfo;

static s32 nwc24ShtRetryRest;
static s32 nwc24ShtFd = -1;
static BOOL NWC24iIsRequestPending;

void REXInit();

void __OSInitNet(void) {
    s32 error;
    OSIOSRev rev;

    //REXInit();
    __OSGetIOSRev(&rev);

    if (rev.idLo <= 4 || rev.idLo == 9) {
        return;
    }

    error = NWC24iPrepareShutdown();
    if (error != 0) {
        if (error < 0) {
            OSReport("Failed to register network shutdown function. %d\n", error);
        }

        error = NWC24SuspendScheduler();
        if (error < 0) {
            OSReport("Failed to suspend the WiiConnect24 scheduler. %d\n", error);
        }
    }

    if(!__OSInIPL){
        error = NWC24iSynchronizeRtcCounter(FALSE);
        if (error != 0) {
            OSReport(
                "Failed to synchronize time with network resource managers. %d\n",
                error);
        }
    }
}

//unused
void __OSSyncTimeWithNetRM(){
    NWC24iSynchronizeRtcCounter(FALSE);
}

void REXInit(){
}

static BOOL NWC24Shutdown_(BOOL final, u32 event);
static inline s32 NWC24iOpenResourceManager_(const char* funcName, const char* path, s32* resultPtr, IPCOpenMode mode);
static inline s32 NWC24iIoctlResourceManager_(const char* funcName, s32 fd, s32 type, void* in, s32 inSize, void* out, s32 outSize);
static inline s32 NWC24iIoctlResourceManagerAsync_(const char* funcName, s32 fd, s32 type, void* in, s32 inSize, void* out, s32 outSize, void* callbackArg);
static inline s32 NWC24iCloseResourceManager_(const char* funcName, s32 fd);
static inline s32 NWC24iCloseResourceManagerAsync_(const char* funcName, s32 fd, void* callbackArg);
static inline s32 CheckCallingStatus(const char* funcName);

DECL_WEAK NWC24Err NWC24iPrepareShutdown(){
    s32 result;
    
    result = 0;
    ShutdownFuncInfo.func = NWC24Shutdown_;
    ShutdownFuncInfo.prio = 0x6e;
    OSRegisterShutdownFunction(&ShutdownFuncInfo);

    if (nwc24ShtFd < 0) {
        result = NWC24iOpenResourceManager_(__FUNCTION__,"/dev/net/kd/request",&nwc24ShtFd,1);
    }
    nwc24ShtRetryRest = 5;

    if (result == 0) {
        result = 1;
    }
    return result;
}

static inline s32 GetRTC(s32* destPtr);
static s32 NWC24iSetRtcCounter_(u32 rtc, u32 param_2);

DECL_WEAK NWC24Err NWC24iSynchronizeRtcCounter(BOOL val){
    s32 result;
    s32 rtc;
    
    result = GetRTC(&rtc);
    
    if (result != 0) {
        return result;
    }else{
        return NWC24iSetRtcCounter_(rtc, val != FALSE);
    }
}

// TODO: two instructions too many. The original has no null check of &fd from the inlined
// NWC24iOpenResourceManager_ and keeps fd in a register; this checks the stack address and keeps fd in memory.
DECL_WEAK s32 NWC24SuspendScheduler(){
    static s32 susResult[8] ALIGN(32);
    s32 rt = 0;
    s32 closeRt = 0;
    s32 fd;

    rt = CheckCallingStatus(__FUNCTION__);
    if (rt < 0) {
        return rt;
    }

    rt = NWC24iOpenResourceManager_(__FUNCTION__, "/dev/net/kd/request", &fd, 0);
    if (rt >= 0) {
        rt = NWC24iIoctlResourceManager_(__FUNCTION__, fd, 1, NULL, 0, susResult, sizeof(susResult));
        if (rt >= 0) {
            rt = susResult[0];
        }

        closeRt = NWC24iCloseResourceManager_(__FUNCTION__, fd);
        if (closeRt < 0) {
            rt = closeRt;
        }
    }

    return rt;
}

//unused
DECL_WEAK s32 NWC24ResumeScheduler(){
    static s32 susResult[8] ALIGN(32);
    s32 rt = 0;
    s32 closeRt = 0;
    s32 fd;

    rt = CheckCallingStatus(__FUNCTION__);
    if (rt < 0) {
        return rt;
    }

    rt = NWC24iOpenResourceManager_(__FUNCTION__, "/dev/net/kd/request", &fd, 0);
    if (rt >= 0) {
        rt = NWC24iIoctlResourceManager_(__FUNCTION__, fd, 3, NULL, 0, susResult, sizeof(susResult));
        if (rt >= 0) {
            rt = susResult[0];
        }

        closeRt = NWC24iCloseResourceManager_(__FUNCTION__, fd);
        if (closeRt < 0) {
            rt = closeRt;
        }
    }

    return rt;
}

static NWC24Err NWC24iRequestShutdown(u32 param_1, NWC24Err* resultOut){
    s32 uVar1;
    static s32 shtBuffer[8] ALIGN(32);
    static s32 shtResult[8] ALIGN(32);
    
    shtBuffer[0] = param_1;
    uVar1 = NWC24iIoctlResourceManagerAsync_(__FUNCTION__, nwc24ShtFd, 0x28, shtBuffer, 0x20, shtResult, 0x20, resultOut);
    return uVar1;
}

static inline BOOL NWC24iIsAsyncRequestPending_();

static BOOL NWC24Shutdown_(BOOL final, u32 event){
    static BOOL shuttingdown = FALSE;
    static NWC24Err result = NWC24_OK;

    if (final) {
        return TRUE;
    }

    if (shuttingdown) {
        if (NWC24iIsAsyncRequestPending_()) {
            return FALSE;
        }

        if (result >= 0) {
            return TRUE;
        }

        if (nwc24ShtRetryRest > 0) {
            shuttingdown = FALSE;
            nwc24ShtRetryRest--;
        } else {
            OSReport("NWC24Shutdown_: Give up!\n");
            return TRUE;
        }
    } else {
        if (NWC24iRequestShutdown(event, &result) >= 0) {
            shuttingdown = TRUE;
        }
    }

    return FALSE;
}

static u32 nwc24TimeCommonBuffer[8] ALIGN(32);
static u32 nwc24TimeCommonResult[8] ALIGN(32);

// TODO: as in NWC24SuspendScheduler.
static s32 NWC24iSetRtcCounter_(u32 rtc, u32 param_2) DECOMP_DONT_INLINE {
    s32 rt = 0;
    s32 closeRt = 0;
    s32 fd;

    rt = CheckCallingStatus(__FUNCTION__);
    if (rt < 0) {
        return rt;
    }

    rt = NWC24iOpenResourceManager_(__FUNCTION__, "/dev/net/kd/time", &fd, IPC_OPEN_NONE);
    if (rt >= 0) {
        nwc24TimeCommonBuffer[0] = rtc;
        nwc24TimeCommonBuffer[1] = param_2;

        rt = NWC24iIoctlResourceManager_(__FUNCTION__, fd, 0x17, nwc24TimeCommonBuffer, 0x20, nwc24TimeCommonResult, 0x20);
        if (rt >= 0) {
            rt = nwc24TimeCommonResult[0];
        }

        closeRt = NWC24iCloseResourceManager_(__FUNCTION__, fd);
        if (rt >= 0) {
            rt = closeRt;
        }
    }

    return rt;
}

static inline s32 NWC24iOpenResourceManager_(const char* funcName, const char* path, s32* resultPtr, IPCOpenMode mode){
    (void)funcName;
    if(resultPtr == NULL){
        return -3;
    }
    
    *resultPtr = IOS_Open(path, mode);
    
    if (*resultPtr < 0) {
        if (*resultPtr == -6) return -29;
        else return -42;
    }else {
        return 0;
    }
}

static inline s32 NWC24iCloseResourceManager_(const char* funcName, s32 fd){
    (void)funcName;
    if (IOS_Close(fd) < 0) return -42;
    else return 0;
}

static s32 CallbackAsyncIpc(s32 result, void* arg);

//unused
static inline s32 NWC24iCloseResourceManagerAsync_(const char* funcName, s32 fd, void* callbackArg){
    (void)funcName;
    if (IOS_CloseAsync(fd, CallbackAsyncIpc, callbackArg) < 0) return -42;
    else {
        NWC24iIsRequestPending = TRUE;
        return 0;
    }
}

static inline s32 NWC24iIoctlResourceManager_(const char* funcName, s32 fd, s32 type, void* in, s32 inSize, void* out, s32 outSize){
    (void)funcName;
    if (IOS_Ioctl(fd, type, in, inSize, out, outSize) < 0) return -42;
    else return 0;
}

static inline s32 NWC24iIoctlResourceManagerAsync_(const char* funcName, s32 fd, s32 type, void* in, s32 inSize, void* out, s32 outSize, void* callbackArg){
    (void)funcName;
    if (IOS_IoctlAsync(fd, type, in, inSize, out, outSize, CallbackAsyncIpc, callbackArg) < 0) return -42;
    else {
        NWC24iIsRequestPending = TRUE;
        return 0;
    }
}

static inline BOOL NWC24iIsAsyncRequestPending_(){
    return NWC24iIsRequestPending;
}

static s32 CallbackAsyncIpc(s32 result, void* arg){
    if (arg != NULL) {
        *(s32*)arg = result;
    }
    NWC24iIsRequestPending = FALSE;
    return 0;
}

static inline s32 CheckCallingStatus(const char* funcName){
    (void)funcName;
    if (OSGetCurrentThread() == NULL) return -1;
    else return 0;
}

static inline s32 GetRTC(s32* destPtr) {
    s64 time;
    u32 bias;
    u32 status;

    while(TRUE){
        status = SCCheckStatus();
    
        if (status == 2) {
            return -1;
        }
        if (status == 0) {
            bias = SCGetCounterBias();
            time = OSGetTime();
            *destPtr = OS_TICKS_TO_SEC(time) - bias;
            return 0;
        }
    }
}
