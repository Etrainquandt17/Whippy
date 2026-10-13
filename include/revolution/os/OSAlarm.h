#ifndef REVOLUTION_OS_OSALARM_H
#define REVOLUTION_OS_OSALARM_H

#include "types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct OSContext OSContext;
typedef s64 OSTime;

// TODO: members. 0x30 bytes, aligned to 8 for its times.
typedef struct OSAlarm {
    union {
        u32 words[0x30 / 4];
        s64 align;
    };
} OSAlarm;

typedef void (*OSAlarmHandler)(OSAlarm* alarm, OSContext* context);

void OSCreateAlarm(OSAlarm* alarm);
void OSSetPeriodicAlarm(OSAlarm* alarm, OSTime start, OSTime period, OSAlarmHandler handler);
void OSCancelAlarm(OSAlarm* alarm);

#ifdef __cplusplus
}
#endif

#endif
