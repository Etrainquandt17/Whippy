#ifndef MSL_FILE_POS_H
#define MSL_FILE_POS_H

#include <xenoblade/types.h>
#include <xenoblade/PowerPC_EABI_Support/include/stl/stdio.h>

#ifdef __cplusplus
extern "C" {
#endif // ifdef __cplusplus

int fseek(FILE* stream, u32 offset, int whence);
int _fseek(FILE* stream, u32 offset, int whence);
int ftell(FILE* stream);
int _ftell(FILE* stream);

#ifdef __cplusplus
};
#endif // ifdef __cplusplus

#endif
