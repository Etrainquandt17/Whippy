#include "libs/libms/libms/libms.h"

static void *(*g_pMalloc)(size_t size);
static void (*g_pFree)(void *arg);

void LMS_SetMemFuncs(void *(*alloc)(size_t size), void (*free)(void *ptr)) {
    g_pMalloc = alloc;
    g_pFree = free;
}

// internal
void *LMSi_Malloc(size_t size) {
    return (g_pMalloc)(size);
}

void LMSi_Free(void *ptr) {
    return (g_pFree)(ptr);
}

int LMSi_MemCmp(const void *p1, const void *p2, int n) {
    for (int i = 0; i < n; i++) {
        if (((const char *)p1)[i] != ((const char *)p2)[i]) {
            return 0;
        }
    }

    return 1;
}

void LMSi_MemCopy(void *p1, const void *p2, int n) {
    for (int i = 0; i < n; i++) {
        ((char *)p1)[i] = ((const char *)p2)[i];
    }
}
