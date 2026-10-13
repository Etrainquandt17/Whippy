#include "scn/step/sfx/MintSuperBackPicture.h"

#include "hel/common/PointerWrapper.h"
#include "hel/math/Direction3.h"
#include "hel/mint/AddOnMathDirection3.h"
#include "metafortress.h"
#include "scn/step/sfx/SuperBackPicture.h"
#include "types.h"

namespace scn {
namespace step {
namespace sfx {

namespace {

hel::common::PointerWrapper<SuperBackPicture> t_obj;

}

namespace MintSuperBackPicture {

#define MF_FUNCTION Register__Q43scn4step3sfx20MintSuperBackPictureFRQ43scn4step3sfx16SuperBackPicture
void Register(SuperBackPicture& obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 key;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xE7E6C103
    after1:
        mflr    r29
        lwz     r19, 0x0(r29)
        stw     r19, expected
    }
    hash = 0xB3;
    asm {
        bl      after2
        opword  0x94611A91
        opword  0x74431C92
        opword  MF_WORD(0x48)
        opword  0xD0AFCD90
        opword  MF_WORD(0x50)
    after2:
        mflr    r19
        lwz     r14, 0x10(r19)
        lwz     r27, 0x8(r19)
        stw     r27, start
        stw     r14, end
    }
    last = end;
    limit = last - start;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash != expected) {
        asm {
            bl      after3
            opword  0xB3118A03
            opword  0x70248A90
            opword  MF_WORD(0xD0)
        after3:
            mflr    r29
            lwz     r22, 0x8(r29)
            stw     r22, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0x9F7F6F0A
            opword  0xDCFB2C90
            opword  MF_WORD(0x100)
        after4:
            mflr    r16
            lwz     r20, 0x0(r16)
            stw     r16, base
            lwz     r30, 0xC(r16)
            stw     r20, offset
            stw     r30, key
        }
        offset = offset + 0xDF;
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        t_obj.set(obj);
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION Unregister__Q43scn4step3sfx20MintSuperBackPictureFRQ43scn4step3sfx16SuperBackPicture
void Unregister(SuperBackPicture&) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 i;
    u32 hash;
    u32 bound;
    u32 word;
    u32 last;
    u32 size;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  MF_WORD(0x24)
    after1:
        mflr    r24
        lwz     r22, 0x4(r24)
        lwz     r21, 0x0(r24)
        add     r21, r21, r24
        stw     r21, start
        add     r22, r22, r21
        stw     r22, end
    }
    hash = 0xBF;
    last = start;
    size = end;
    size = size - last;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0xA877B075
    after2:
        mflr    r28
        lwz     r18, 0x0(r28)
        stw     r18, expected
    }
    i = -1;
    word = last - 1;
    bound = size - 1;
    while (i != bound) {
        i += 2;
        size = hash << 4;
        last = hash >> 28;
        last = size ^ last;
        hash = word - i;
        hash = *(u16*)hash;
        hash = last ^ hash;
    }
    i = hash << 3;
    hash += i;
    i = hash >> 11;
    hash ^= i;
    i = hash << 15;
    hash += i;
    i = expected;
    if (hash == i) {
        t_obj.reset();
    } else {
        asm {
            bl      after3
            opword  0x84992B81
            opword  MF_WORD(0xDC)
        after3:
            mflr    r24
            lwz     r20, 0x4(r24)
            stw     r20, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x100)
            opword  0x303B5981
            opword  0x1C7B3491
            opword  MF_WORD(0x10C)
        after4:
            mflr    r20
            lwz     r29, 0xC(r20)
            stw     r29, key
            lwz     r29, 0x0(r20)
            stw     r20, base
            stw     r29, offset
        }
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    }
}
#undef MF_FUNCTION

void RequestEffect(effect::Kind kind) {
    t_obj->requestEffect(kind);
}

void RequestEffectN(effect::Kind kind) {
    t_obj->requestEffect(kind, hel::mint::AddOnMathDirection3::Get());
}

void ReleaseEffect() {
    t_obj->releaseEffect();
}

void RequestEffect2(effect::Kind kind) {
    t_obj->requestEffect2(kind);
}

void RequestEffect2N(effect::Kind kind) {
    t_obj->requestEffect2(kind, hel::mint::AddOnMathDirection3::Get());
}

void ReleaseEffect2() {
    t_obj->releaseEffect2();
}

void RequestEffectNonStop(effect::Kind kind) {
    t_obj->requestEffectNonStop(kind);
}

void RequestEffectNonStopN(effect::Kind kind) {
    t_obj->requestEffectNonStop(kind, hel::mint::AddOnMathDirection3::Get());
}

void ReleaseEffectNonStop() {
    t_obj->releaseEffectNonStop();
}

#define MF_FUNCTION RequestEffectNonStop2__Q43scn4step3sfx20MintSuperBackPictureFQ43scn4step6effect4Kind
void RequestEffectNonStop2(effect::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 key;
    volatile u32 offset;
    u32 word;
    u32 last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x4DB02D20
    after1:
        mflr    r24
        lwz     r22, 0x0(r24)
        stw     r22, expected
        bl      after2
        opword  0x54F0AD91
        opword  MF_WORD(0x44)
        opword  0xE9D24D03
        opword  0x692DF205
        opword  MF_WORD(0x50)
        opword  0x408F9B92
        opword  0x50A1CE90
    after2:
        mflr    r22
        lwz     r18, 0x10(r22)
        lwz     r21, 0x4(r22)
        stw     r21, end
        stw     r18, start
    }
    last = end;
    word = start;
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash == 0) {
        t_obj->requestEffectNonStop2(kind);
    } else {
        asm {
            bl      after3
            opword  0xF843BA91
            opword  0x0CC53993
            opword  0xA74D150D
            opword  MF_WORD(0xFC)
        after3:
            mflr    r27
            lwz     r16, 0xC(r27)
            stw     r16, -0x4(r1)
            stw     r27, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r27, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x120)
            opword  0x1CF18B80
            opword  0xB4FEBB93
            opword  MF_WORD(0x12C)
        after4:
            mflr    r16
            lwz     r25, 0xC(r16)
            stw     r25, key
            lwz     r25, 0x0(r16)
            stw     r16, base
            stw     r25, offset
        }
        offset = offset + 0xE4;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

void RequestEffectNonStop2N(effect::Kind kind) {
    t_obj->requestEffectNonStop2(kind, hel::mint::AddOnMathDirection3::Get());
}

void ReleaseEffectNonStop2() {
    t_obj->releaseEffectNonStop2();
}

}
}
}
}
