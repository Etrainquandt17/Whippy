#include "scn/step/sfx/MintSuperFade.h"

#include "hel/common/PointerWrapper.h"
#include "metafortress.h"
#include "scn/step/sfx/SuperFade.h"
#include "types.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace sfx {

namespace {

PointerWrapper<SuperFade> t_obj;

}

namespace MintSuperFade {

#define MF_FUNCTION Register__Q43scn4step3sfx13MintSuperFadeFRQ43scn4step3sfx9SuperFade
void Register(SuperFade& obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    u32 i;
    u32 word;
    u32 size;
    u32 hash;

    hash = 0x811C9E53;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  MF_WORD(0x30)
    after1:
        mflr    r17
        lwz     r24, 0x0(r17)
        lwz     r29, 0x4(r17)
        add     r24, r24, r17
        add     r29, r29, r24
        stw     r24, start
        stw     r29, end
    }
    size = end - start + 1;
    i = 1;
    word = start;
    for (; i != size; i += 2) {
        hash ^= *(u16*)(word + i - 1);
        hash *= 0x010001D1;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x94)
        opword  0x67C3546F
    after2:
        mflr    r18
        lwz     r26, 0x0(r18)
        stw     r26, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if ((hash ^ expected) == 0) {
        t_obj.set(obj);
    } else {
        asm {
            bl      after3
            opword  0x10F38A07
            opword  MF_WORD(0xD8)
        after3:
            mflr    r30
            lwz     r21, 0x4(r30)
            stw     r21, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r21
            bl      after4
            opword  MF_WORD(0xFC)
            opword  0x2652C704
            opword  MF_WORD(0x104)
        after4:
            mflr    r19
            lwz     r23, 0x0(r19)
            lwz     r18, 0x8(r19)
            stw     r18, key
            stw     r23, offset
            stw     r19, base
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION Unregister__Q43scn4step3sfx13MintSuperFadeFRQ43scn4step3sfx9SuperFade
void Unregister(SuperFade&) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  0x3058A180
        opword  0x90E1D180
        opword  MF_WORD(0x2C)
        opword  0x2FFB7600
        opword  MF_WORD(0x34)
    after1:
        mflr    r22
        lwz     r29, 0x8(r22)
        stw     r29, start
        lwz     r29, 0x10(r22)
        stw     r29, end
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash *= 151;
        hash += *(u16*)word;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x7C)
        opword  0x35A76FF8
    after2:
        mflr    r16
        lwz     r30, 0x0(r16)
        stw     r30, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash = __cntlzw((hash & ~expected) | (expected & ~hash));
    hash = (hash >> 5) | ((hash >> 5) << 8);
    if (hash == 0) {
        t_obj.reset();
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0xDC)
        after3:
            mflr    r16
            lwz     r17, 0x0(r16)
            stw     r17, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r17
            bl      after4
            opword  MF_WORD(0x100)
            opword  MF_WORD(0x104)
        after4:
            mflr    r26
            lwz     r16, 0x0(r26)
            stw     r26, base
            lwz     r21, 0x4(r26)
            stw     r16, offset
            stw     r21, key
        }
        response = offset - key;
        response = response + base;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION SetBack__Q43scn4step3sfx13MintSuperFadeFb
void SetBack(bool back) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
    after1:
        mflr    r21
        lwz     r15, 0x4(r21)
        stw     r15, end
        lwz     r23, 0x0(r21)
        stw     r23, start
    }
    hash = 0xC1;
    last = end;
    word = start;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0x88)
        opword  0x9EB9C3DE
    after2:
        mflr    r24
        lwz     r19, 0x0(r24)
        stw     r19, expected
    }
    hash += hash << 15;
    if (hash - expected == 0) {
        t_obj->setBack(back);
    } else {
        asm {
            bl      after3
            opword  0xC08E8280
            opword  0x941B1C93
            opword  MF_WORD(0xD0)
        after3:
            mflr    r16
            lwz     r27, 0x8(r16)
            stw     r27, -0x4(r1)
            stw     r16, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r16, -0x8(r1)
            mtlr    r27
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0xC4BF6E93
            opword  MF_WORD(0xFC)
        after4:
            mflr    r14
            lwz     r25, 0x0(r14)
            stw     r14, base
            lwz     r28, 0x8(r14)
            stw     r25, offset
            stw     r28, key
        }
        offset = offset + 0x30;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::sfx::MintSuperFade
