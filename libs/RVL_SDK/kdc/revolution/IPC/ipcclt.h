#ifndef RVL_SDK_IPC_CLT_H
#define RVL_SDK_IPC_CLT_H
#include <kdc/types.h>

#include <kdc/revolution/OS.h>
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    IPC_RESULT_OK = 0,
    IPC_RESULT_ACCESS = -1,
    IPC_RESULT_EXISTS = -2,
    IPC_RESULT_INTR                 = -3,
    IPC_RESULT_INVALID = -4,
    IPC_RESULT_CONN_MAX_INTERNAL = -5,
    IPC_RESULT_NOEXISTS = -6,
    IPC_RESULT_EMPTYQUEUE           = -7,
    IPC_RESULT_BUSY = -8,
    IPC_RESULT_UNKNOWN  = -9,
    IPC_RESULT_NOTREADY             = -10,
    IPC_RESULT_ECC                  = -11,
    IPC_RESULT_ECC_CRIT = -12,
    IPC_RESULT_BADBLOCK             = -13,
    IPC_RESULT_INVALID_OBJTYPE      = -14,
    IPC_RESULT_INVALID_RNG          = -15,
    IPC_RESULT_INVALID_FLAG         = -16,
    IPC_RESULT_INVALID_FORMAT       = -17,
    IPC_RESULT_INVALID_VERSION      = -18,
    IPC_RESULT_INVALID_SIGNATURE    = -19,
    IPC_RESULT_VERIFY_FAILED        = -20,
    IPC_RESULT_INTERNAL_FAILURE     = -21,
    IPC_RESULT_ALLOC_FAILED         = -22,
    IPC_RESULT_INVALID_SIZE         = -23,
} IPCResult;

typedef enum {
    IPC_REQ_NONE,
    IPC_REQ_OPEN,
    IPC_REQ_CLOSE,
    IPC_REQ_READ,
    IPC_REQ_WRITE,
    IPC_REQ_SEEK,
    IPC_REQ_IOCTL,
    IPC_REQ_IOCTLV
} IPCRequestType;

typedef enum {
    IPC_OPEN_NONE = 0,
    IPC_OPEN_READ = (1 << 0),
    IPC_OPEN_WRITE = (1 << 1),
    IPC_OPEN_RW = IPC_OPEN_READ | IPC_OPEN_WRITE
} IPCOpenMode;

typedef enum {
    IPC_SEEK_BEG,
    IPC_SEEK_CUR,
    IPC_SEEK_END,
} IPCSeekMode;

typedef s32 (*IPCAsyncCallback)(s32 result, void* arg);

typedef struct IPCIOVector {
    void* base; // at 0x0
    u32 length; // at 0x4
} IPCIOVector;

typedef struct IPCOpenArgs {
    const char* path; // at 0x0
    IPCOpenMode mode; // at 0x4
} IPCOpenArgs;

typedef struct IPCReadWriteArgs {
    void* data; // at 0x0
    u32 length; // at 0x4
} IPCReadWriteArgs;

typedef struct IPCSeekArgs {
    s32 offset;       // at 0x0
    IPCSeekMode mode; // at 0x4
} IPCSeekArgs;

typedef struct IPCIoctlArgs {
    s32 type;    // at 0x0
    void* in;    // at 0x4
    s32 inSize;  // at 0x8
    void* out;   // at 0xC
    s32 outSize; // at 0x10
} IPCIoctlArgs;

typedef struct IPCIoctlvArgs {
    s32 type;             // at 0x0
    u32 inCount;          // at 0x4
    u32 outCount;         // at 0x8
    IPCIOVector* vectors; // at 0xC
} IPCIoctlvArgs;

typedef struct IPCRequest {
    IPCRequestType type; // at 0x0
    s32 ret;             // at 0x4
    s32 fd;              // at 0x8
    union {
        IPCOpenArgs open;
        IPCReadWriteArgs rw;
        IPCSeekArgs seek;
        IPCIoctlArgs ioctl;
        IPCIoctlvArgs ioctlv;
    }; // at 0xC
} IPCRequest;

typedef struct IPCRequestEx {
    IPCRequest base;           // at 0x0
    IPCAsyncCallback callback; // at 0x20
    void* callbackArg;         // at 0x24
    BOOL reboot;               // at 0x28
    OSThreadQueue queue;       // at 0x2C
    char padding[64 - 0x34];
} IPCRequestEx;

s32 IPCCltInit(void);
s32 IOS_OpenAsync(const char* path, IPCOpenMode mode, IPCAsyncCallback callback,
                  void* callbackArg);
s32 IOS_Open(const char* path, IPCOpenMode mode);
s32 IOS_CloseAsync(s32 fd, IPCAsyncCallback callback, void* callbackArg);
s32 IOS_Close(s32 fd);
s32 IOS_ReadAsync(s32 fd, void* buf, s32 len, IPCAsyncCallback callback,
                  void* callbackArg);
s32 IOS_Read(s32 fd, void* buf, s32 len);
s32 IOS_WriteAsync(s32 fd, const void* buf, s32 len, IPCAsyncCallback callback,
                   void* callbackArg);
s32 IOS_Write(s32 fd, const void* buf, s32 len);
s32 IOS_SeekAsync(s32 fd, s32 offset, IPCSeekMode mode,
                  IPCAsyncCallback callback, void* callbackArg);
s32 IOS_Seek(s32 fd, s32 offset, IPCSeekMode mode);
s32 IOS_IoctlAsync(s32 fd, s32 type, void* in, s32 inSize, void* out,
                   s32 outSize, IPCAsyncCallback callback, void* callbackArg);
s32 IOS_Ioctl(s32 fd, s32 type, void* in, s32 inSize, void* out, s32 outSize);
s32 IOS_IoctlvAsync(s32 fd, s32 type, s32 inCount, s32 outCount,
                    IPCIOVector* vectors, IPCAsyncCallback callback,
                    void* callbackArg);
s32 IOS_Ioctlv(s32 fd, s32 type, s32 inCount, s32 outCount,
               IPCIOVector* vectors);
s32 IOS_IoctlvReboot(s32 fd, s32 type, s32 inCount, s32 outCount,
                     IPCIOVector* vectors);

#ifdef __cplusplus
}
#endif
#endif
