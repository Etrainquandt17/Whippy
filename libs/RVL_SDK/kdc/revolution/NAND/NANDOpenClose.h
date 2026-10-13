#ifndef RVL_SDK_NAND_OPEN_CLOSE_H
#define RVL_SDK_NAND_OPEN_CLOSE_H
#include <kdc/types.h>

#include <kdc/revolution/NAND/nand.h>
#ifdef __cplusplus
extern "C" {
#endif

s32 NANDOpen(const char* path, NANDFileInfo* info, u8 mode);
s32 NANDPrivateOpen(const char* path, NANDFileInfo* info, u8 mode);
s32 NANDOpenAsync(const char* path, NANDFileInfo* info, u8 mode,
                  NANDAsyncCallback callback, NANDCommandBlock* block);
s32 NANDPrivateOpenAsync(const char* path, NANDFileInfo* info, u8 mode,
                         NANDAsyncCallback callback, NANDCommandBlock* block);

s32 NANDClose(NANDFileInfo* info);
s32 NANDCloseAsync(NANDFileInfo* info, NANDAsyncCallback callback,
                   NANDCommandBlock* block);

#ifdef __cplusplus
}
#endif
#endif
