#include "util/Mutex.h"

#include "metafortress.h"

namespace util {

#define MF_FUNCTION __ct__Q24util5MutexFv
Mutex::Mutex() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x64D01A81
    after1:
        mflr    r16
        lwz     r22, 0x0(r16)
        stw     r22, start
        bl      after2
        opword  0x57B4BE02
        opword  0xC303A402
        opword  MF_WORD(0x48)
        opword  0xF00DCA91
        opword  0xC703D70B
    after2:
        mflr    r16
        lwz     r22, 0x8(r16)
        stw     r22, end
    }
    last = end;
    limit = last - start + 1;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xA8)
        opword  0xAA1BE1AB
    after3:
        mflr    r17
        lwz     r15, 0x0(r17)
        stw     r15, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash == expected) {
        OSInitMutex(&mMutex);
    } else {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 subtrahend;
        volatile u32 base;

        asm {
            bl      after4
            opword  MF_WORD(0xE8)
        after4:
            mflr    r19
            lwz     r21, 0x0(r19)
            stw     r21, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r21
            bl      after5
            opword  MF_WORD(0x10C)
            opword  0x3B51C203
            opword  0x24E70581
            opword  MF_WORD(0x118)
        after5:
            mflr    r14
            lwz     r20, 0xc(r14)
            stw     r20, subtrahend
            lwz     r20, 0x0(r14)
            stw     r14, base
            stw     r20, offset
        }
        offset = offset - 0xE;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

void Mutex::lock() {
    OSLockMutex(&mMutex);
}

void Mutex::unlock() {
    OSUnlockMutex(&mMutex);
}

ScopedMutex::ScopedMutex(Mutex& mutex)
    : mMutex(&mutex) {
    mMutex->lock();
}

ScopedMutex::~ScopedMutex() {
    mMutex->unlock();
}

}
