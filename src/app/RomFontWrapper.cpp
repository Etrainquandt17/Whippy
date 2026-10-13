#include "app/RomFontWrapper.h"

#include "hel/common/ExplicitSingleton.h"
#include "mem/HeapExp.h"
#include "mem/Memory.h"
#include "metafortress.h"

namespace app {

#define MF_FUNCTION __ct__Q23app14RomFontWrapperFv
RomFontWrapper::RomFontWrapper()
    : mBlock(nw4r::ut::RomFont::GetRequireBufferSize(), 0x20, hel::common::ExplicitSingleton<mem::Memory>::object_->mem2FixHeap())
    , mFont() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 base;
    volatile u32 subtrahend;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    mFont.Load(mBlock.block().startAddress());
    asm {
        bl      ended
        opword  MF_WORD(0x70)
    ended:
        mflr    r28
        lwz     r21, 0(r28)
        stw     r21, end
        bl      ranged
        opword  0xF8F8AD92
        opword  0x50A6BF92
        opword  MF_WORD(0x8C)
        opword  0x3C33AF0C
    ranged:
        mflr    r28
        lwz     r21, 8(r28)
        stw     r21, start
        bl      stored
        opword  MF_WORD(0xA4)
        opword  0x94AB28DF
    stored:
        mflr    r17
        lwz     r28, 0(r17)
        stw     r28, expected
    }
    last = end;
    limit = last - start + 1;
    hash = 0x811C9DC5;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *reinterpret_cast<u16*>(last - 1 - i);
        hash *= 0x01000181;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash != expected) {
        asm {
            bl      located
            opword  0xBCACBD91
            opword  0x46A1AF0F
            opword  0xA5726104
            opword  MF_WORD(0x134)
        located:
            mflr    r29
            lwz     r20, 0xC(r29)
            stw     r20, -4(r1)
            stw     r29, 0(r1)
            stw     r20, -4(r1)
            stw     r29, -8(r1)
            mtlr    r20
            bl      based
            opword  MF_WORD(0x158)
            opword  0x650DE802
            opword  MF_WORD(0x160)
        based:
            mflr    r28
            lwz     r30, 0(r28)
            lwz     r25, 8(r28)
            stw     r25, subtrahend
            stw     r30, offset
            stw     r28, base
        }
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

RomFontWrapper::~RomFontWrapper() {
    mFont.Unload();
}

#define MF_FUNCTION font__Q23app14RomFontWrapperFv
nw4r::ut::RomFont& RomFontWrapper::font() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0x811C9E29;
    asm {
        bl      after1
        opword  0xF5198E07
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
        opword  0xA8B21990
        opword  0xCD145302
    after1:
        mflr    r27
        lwz     r22, 0x8(r27)
        lwz     r16, 0x4(r27)
        stw     r16, start
        stw     r22, end
    }
    word = start;
    last = end;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x010001AB;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x88)
        opword  0xAA9D80B2
    after2:
        mflr    r29
        lwz     r16, 0x0(r29)
        stw     r16, expected
    }
    hash -= expected;
    if (hash == 0) {
        return mFont;
    } else {
        volatile u32 response;
        volatile u32 key;
        volatile u32 base;
        volatile u32 offset;

        asm {
            bl      after3
            opword  MF_WORD(0xB8)
        after3:
            mflr    r23
            addi    r30, r23, 0x10
            mtlr    r30
            lwz     r16, 0x0(r23)
            stw     r16, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r23, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0xE0)
            opword  0x6117C808
            opword  MF_WORD(0xE8)
        after4:
            mflr    r26
            lwz     r25, 0x0(r26)
            lwz     r21, 0x8(r26)
            stw     r21, key
            stw     r25, offset
            stw     r26, base
        }
        offset = offset - 0x7B;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    }
}
#undef MF_FUNCTION

}  // namespace app
