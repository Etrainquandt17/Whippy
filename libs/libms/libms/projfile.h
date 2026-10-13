#ifndef LIBMS_PROJFILE_H
#define LIBMS_PROJFILE_H

#include "libs/libms/common.h"
#include <libs/libms/msl/cstddef>

#ifdef __cplusplus
extern "C" {
#endif

struct ProjectInfo;

struct ProjectInfo *LMS_InitProject(void *data);
const wchar_t *LMS_GetTagGroupName(struct ProjectInfo *info, unsigned short group);
const wchar_t *LMS_GetTagName(struct ProjectInfo *info, unsigned short group, unsigned short tag);
const wchar_t *LMS_GetTagListItemName(struct ProjectInfo *info, unsigned short group, unsigned short tag, unsigned short param,
                                      unsigned short item);

#ifdef __cplusplus
}
#endif

#endif
