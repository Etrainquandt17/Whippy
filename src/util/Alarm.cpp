#include "util/Alarm.h"

#include "metafortress.h"
#include "util/DisableInterrupts.h"

namespace {

OSTime T_PERIOD = (1.0f / 60.0f) * (*reinterpret_cast<u32*>(0x800000F8) / 4);

void t_handler(OSAlarm*, OSContext*) {}

}

namespace util {

Alarm::Alarm() {
    init();
    SetInstance(*this);
}

Alarm::~Alarm() {
    UnsetInstance();
    final();
}

#define MF_FUNCTION init__Q24util5AlarmFv
void Alarm::init() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    OSCreateAlarm(&mAlarm);
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xD0B7EB80
    after1:
        mflr    r25
        lwz     r24, 0x0(r25)
        add     r24, r24, r25
        stw     r24, start
        bl      after2
        opword  MF_WORD(0x48)
        opword  0x401E2693
    after2:
        mflr    r25
        lwz     r21, 0x0(r25)
        add     r24, r24, r21
        stw     r24, end
    }
    hash = 0x811C9E53;
    asm {
        bl      after3
        opword  MF_WORD(0x6C)
        opword  0x85DC1376
    after3:
        mflr    r30
        lwz     r25, 0x0(r30)
        stw     r25, expected
    }
    base = start;
    limit = end - base + 1;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    hash -= expected;
    if (hash != 0) {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 unused;

        asm {
            bl      after4
            opword  MF_WORD(0xD0)
        after4:
            mflr    r18
            lwz     r20, 0x0(r18)
            stw     r20, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r20
            bl      after5
            opword  MF_WORD(0xF4)
            opword  MF_WORD(0xF8)
        after5:
            mflr    r21
            stw     r21, base2
            lwz     r17, 0x0(r21)
            stw     r17, offset
            lwz     r25, 0x4(r21)
            stw     r25, unused
        }
        offset = offset - 0x6B;
        unused = 0;
        response = offset;
        response = response + base2;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    } else {
        OSSetPeriodicAlarm(&mAlarm, T_PERIOD, T_PERIOD, t_handler);
    }
}
#undef MF_FUNCTION

void Alarm::final() {
    DisableInterrupts lock;
    OSCancelAlarm(&mAlarm);
}

}  // namespace util
