#ifndef RVL_SDK_DVD_ID_UTILS_H
#define RVL_SDK_DVD_ID_UTILS_H
#include <xenoblade/types.h>

#include <xenoblade/RVL_SDK/include/revolution/dvd/dvd.h>
#ifdef __cplusplus
extern "C" {
#endif

BOOL DVDCompareDiskID(const DVDDiskID* id1, const DVDDiskID* id2);

#ifdef __cplusplus
}
#endif
#endif
