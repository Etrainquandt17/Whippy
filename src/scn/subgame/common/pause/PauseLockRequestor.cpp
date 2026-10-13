#include "scn/subgame/common/pause/PauseLockRequestor.h"

#include "metafortress.h"

namespace scn {
namespace subgame {
namespace common {
namespace pause {

PauseLockRequestor::PauseLockRequestor()
    : mIsLocked(false)
    , mIsSELocked(false) {
}

#define MF_FUNCTION __dt__Q53scn7subgame6common5pause18PauseLockRequestorFv
PauseLockRequestor::~PauseLockRequestor() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x3C)
        opword  0xC59606C4
    after1:
        mflr    r30
        lwz     r24, 0x0(r30)
        stw     r24, expected
        bl      after2
        opword  MF_WORD(0x54)
    after2:
        mflr    r29
        lwz     r26, 0x0(r29)
        add     r26, r26, r29
        stw     r26, start
        bl      after3
        opword  0x38557881
        opword  0xF8244681
        opword  MF_WORD(0x74)
    after3:
        mflr    r29
        lwz     r27, 0x8(r29)
        add     r26, r26, r27
        stw     r26, end
    }
    last = end;
    p = start;
    if (mIsLocked) {
        cancel();
    }
    hash = 0;
    for (; p != last; p += 2) {
        hash += *(u16*)p;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected != 0 || mIsSELocked) {
        cancelSELock();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION request__Q53scn7subgame6common5pause18PauseLockRequestorFv
void PauseLockRequestor::request() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash = 0x811C9E07;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x868A7774
    after1:
        mflr    r30
        lwz     r20, 0x0(r30)
        stw     r20, expected
        bl      after2
        opword  0xDE34A90A
        opword  MF_WORD(0x40)
        opword  0x43CC2A03
        opword  MF_WORD(0x48)
        opword  0x7F525008
        opword  0xBB4CB202
    after2:
        mflr    r14
        lwz     r16, 0xc(r14)
        stw     r16, end
        lwz     r26, 0x4(r14)
        stw     r26, start
    }
    u32 i = 1;
    u32 base = start;
    u32 limit = end - base + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001A7;
        i += 2;
    }
    mIsLocked = expected == hash;
    util::AccessProtectedSingleton<Manager>::object_->requestLockPause();
}
#undef MF_FUNCTION

#define MF_FUNCTION cancel__Q53scn7subgame6common5pause18PauseLockRequestorFv
void PauseLockRequestor::cancel() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 size;
    u32 last;
    u32 base;
    u32 first;
    u32 i;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x5466FB91
        opword  0x1839DD91
        opword  MF_WORD(0x30)
        opword  0x08C06F93
        opword  0x8FD2930C
    after1:
        mflr    r16
        lwz     r29, 0x0(r16)
        add     r29, r29, r16
        lwz     r22, 0xc(r16)
        stw     r29, start
        add     r22, r22, r29
        stw     r22, end
    }
    hash = 0;
    last = end;
    first = start;
    size = last - first;
    i = -1;
    base = last - 1;
    while (i != size - 1) {
        i += 2;
        hash *= 193;
        hash += *(u16*)(base - i);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x591883B4
    after2:
        mflr    r15
        lwz     r24, 0x0(r15)
        stw     r24, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    mIsLocked = expected != hash;
    util::AccessProtectedSingleton<Manager>::object_->requestUnlockPause();
}
#undef MF_FUNCTION

#define MF_FUNCTION requestSELock__Q53scn7subgame6common5pause18PauseLockRequestorFv
void PauseLockRequestor::requestSELock() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    PauseLockRequestor* self;
    u32 i;
    u32 size;
    bool flag;
    u32 hash;
    u32 p;
    u32 last;
    u32 t;

    self = this;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xEA2C80C8
    after1:
        mflr    r16
        lwz     r25, 0x0(r16)
        stw     r25, expected
        bl      after2
        opword  0x731DE30A
        opword  0xF8F94580
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
        opword  0xFCFE6B80
    after2:
        mflr    r29
        lwz     r28, 0xc(r29)
        lwz     r24, 0x8(r29)
        add     r28, r24, r28
        stw     r28, end
        stw     r24, start
    }
    i = 1;
    last = end;
    t = start;
    t = last - t;
    size = t + 1;
    hash = 0xB5;
    p = last - 1;
    while (i != size) {
        t = hash << 4;
        last = hash >> 28;
        last = t ^ last;
        hash = p - i;
        hash = *(u16*)hash;
        hash = last ^ hash;
        i += 2;
    }
    flag = true;
    self->mIsSELocked = flag;
    size = hash << 3;
    hash += size;
    size = hash >> 11;
    hash ^= size;
    size = hash << 15;
    hash += size;
    size = expected;
    hash = hash - size;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xE0)
        after3:
            mflr    r19
            lwz     r23, 0x0(r19)
            stw     r23, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x104)
            opword  0x7C254A91
            opword  MF_WORD(0x10C)
        after4:
            mflr    r19
            lwz     r30, 0x0(r19)
            lwz     r25, 0x8(r19)
            stw     r25, key
            stw     r30, offset
            stw     r19, base
        }
        offset = offset ^ 0x9F;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        util::AccessProtectedSingleton<Manager>::object_->requestLockPauseSE();
    }
}
#undef MF_FUNCTION

void PauseLockRequestor::cancelSELock() {
    mIsSELocked = false;
    util::AccessProtectedSingleton<Manager>::object_->requestUnlockPauseSE();
}

}}}}  // namespace scn::subgame::common::pause
