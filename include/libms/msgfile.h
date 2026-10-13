#ifndef LIBMS_MSGFILE_H
#define LIBMS_MSGFILE_H

#ifdef __cplusplus
extern "C" {
#endif

struct MsbtInfo;

struct MsbtInfo* LMS_InitMessage(void* data);
void LMS_CloseMessage(struct MsbtInfo* info);
int LMS_GetTextNum(struct MsbtInfo* info);
int LMS_GetTextIndexByLabel(struct MsbtInfo* info, const char* label);
const wchar_t* LMS_GetText(struct MsbtInfo* info, int index);

#ifdef __cplusplus
}
#endif

#endif
