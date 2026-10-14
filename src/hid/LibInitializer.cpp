#include "hid/LibInitializer.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "metafortress.h"
#include "revolution/kpad.h"
#include "types.h"

using hel::common::ExplicitSingleton;

namespace {

#define MF_FUNCTION t_wpadAlloc__32_unnamed_LibInitializer_prt_cpp_FUl
void* t_wpadAlloc(u32 size) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 word;
    u32 hash;
    u32 t;
    u32 last;

    hash = 0;
    asm {
        bl      after1
        opword  0xE2AE4A07
        opword  0x10A21D0C
        opword  MF_WORD(0x30)
        opword  0x7B289601
        opword  0x60ADF280
        opword  MF_WORD(0x3C)
        opword  0xD46FB180
    after1:
        mflr    r29
        lwz     r23, 0x8(r29)
        lwz     r27, 0x14(r29)
        stw     r27, end
        stw     r23, start
    }
    word = start;
    last = end;
    for (; word != last; word += 2) {
        hash *= 0x6B;
        t = *reinterpret_cast<u16*>(word);
        hash += t;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x80)
        opword  0x62726A4A
    after2:
        mflr    r16
        lwz     r20, 0x0(r16)
        stw     r20, expected
    }
    t = hash << 13;
    hash += t;
    t = hash >> 7;
    hash ^= t;
    t = hash << 3;
    hash += t;
    t = hash >> 17;
    hash ^= t;
    t = hash << 5;
    hash += t;
    t = expected;
    t = hash & ~t;
    word = expected;
    word = word & ~hash;
    word = t | word;
    hash = __cntlzw(word);
    word = hash >> 5;
    hash = word * 0x22;
    hash = word + hash;
    if (hash == 0) {
        asm {
            bl      after3
            opword  0xCC9F3E81
            opword  MF_WORD(0xF0)
        after3:
            mflr    r18
            lwz     r23, 0x4(r18)
            stw     r23, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0x114)
            opword  MF_WORD(0x118)
        after4:
            mflr    r14
            lwz     r22, 0x0(r14)
            lwz     r19, 0x4(r14)
            stw     r19, addend
            stw     r22, offset
            stw     r14, base
        }
        offset = offset + 0x70;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        return ExplicitSingleton<mem::Memory>::object_->mem2FixHeap().alloc(size);
    }
}
#undef MF_FUNCTION

int t_wpadFree(void* ptr) {
    ExplicitSingleton<mem::Memory>::object_->mem2FixHeap().free(ptr);
    return 1;
}

}

namespace hid {

#define MF_FUNCTION __ct__Q23hid14LibInitializerFv
LibInitializer::LibInitializer() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 addend;
    volatile u32 offset;
    volatile u32 response;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    hash = 0;
    WPADRegisterAllocator(t_wpadAlloc, t_wpadFree);
    asm {
        bl      after1
        opword  MF_WORD(0x44)
        opword  0x01AF8259
    after1:
        mflr    r26
        lwz     r27, 0x0(r26)
        stw     r27, expected
    }
    KPADInit();
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0xFEA35001
        opword  MF_WORD(0x68)
        opword  0xCCF41681
        opword  0x5CE26080
    after2:
        mflr    r20
        lwz     r17, 0x8(r20)
        stw     r17, end
        lwz     r14, 0x0(r20)
        stw     r14, start
    }
    KPADReset();
    limit = end - start + 1;
    i = 1;
    first = start;
    for (s32 chan = 0; chan < 4; chan++) {
        KPADSetPosParam(chan, 0.1f, 0.5f);
        KPADSetBtnRepeat(chan, 0.2f, 0.1f);
        KPADSetAccParam(chan, 0.07f, 1.0f);
        KPADSetDistParam(chan, 0.07f, 1.0f);
        KPADEnableAimingMode(chan);
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *reinterpret_cast<u16*>(first + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    PADInit();
    limit = hash << 15;
    hash += limit;
    limit = expected;
    limit = hash ^ limit;
    if (limit != 0) {
        asm {
            bl      after3
            opword  0x4872EC92
            opword  MF_WORD(0x15C)
        after3:
            mflr    r24
            lwz     r16, 0x4(r24)
            stw     r16, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x180)
            opword  MF_WORD(0x184)
        after4:
            mflr    r23
            stw     r23, base
            lwz     r24, 0x0(r23)
            stw     r24, offset
            lwz     r19, 0x4(r23)
            stw     r19, addend
        }
        offset = offset + 0x95;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else {
        // Five milliseconds: the bus clock is at 0x800000F8, and the timer runs at a quarter of it.
        OSSleepTicks(static_cast<s64>(5) * ((*reinterpret_cast<u32*>(0x800000F8) / 4) / 1000));
    }
}
#undef MF_FUNCTION

LibInitializer::~LibInitializer() {
    KPADShutdown();
}

}  // namespace hid
