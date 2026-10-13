#include "mintglue/Scn__Title__Chara.h"

#include "metafortress.h"
#include "mintglue/WrapNative.h"
#include "scn/title/Chara.h"

namespace mintglue {

void Scn__Title__Chara::AddOn(mintvm::VMCore& core) {
    core.addNativePod("Scn.Title.Chara", sizeof(Scn__Title__Chara));
    MINT_NATIVE_POD_METHOD(core, "Scn.Title.Chara", "void changeAnim(string,int)", changeAnim, &Scn__Title__Chara::changeAnim);
    MINT_NATIVE_POD_METHOD(core, "Scn.Title.Chara", "bool isAnimLooped()", isAnimLooped, &Scn__Title__Chara::isAnimLooped);
    MINT_NATIVE_POD_METHOD(core, "Scn.Title.Chara", "void effectRequestN(int,string)", effectRequestN, &Scn__Title__Chara::effectRequestN);
}

#define MF_FUNCTION changeAnim__Q28mintglue17Scn__Title__CharaFPCci
void Scn__Title__Chara::changeAnim(const char* name, int frame) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 addend;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  0x4809B680
        opword  MF_WORD(0x38)
        opword  0x353CE30D
        opword  0x7042A892
        opword  MF_WORD(0x44)
        opword  0xF0072F09
    after1:
        mflr    r15
        lwz     r25, 0x4(r15)
        lwz     r19, 0x10(r15)
        add     r19, r25, r19
        stw     r25, start
        stw     r19, end
    }
    word = start;
    last = end;
    for (;;) {
        if (word == last) {
            break;
        }
        hash ^= *(u16*)word;
        hash *= 0x01000181;
        word += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0x40F0CA88
    after2:
        mflr    r16
        lwz     r18, 0x0(r16)
        stw     r18, expected
    }
    hash += hash << 15;
    hash -= expected;
    hash |= hash << 8;
    if (hash == 0) {
        mChara->changeAnim(name, frame);
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x10C)
        after3:
            mflr    r20
            lwz     r17, 0x0(r20)
            stw     r17, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r17
            bl      after4
            opword  MF_WORD(0x130)
            opword  MF_WORD(0x134)
        after4:
            mflr    r27
            stw     r27, base
            lwz     r30, 0x0(r27)
            stw     r30, offset
            lwz     r21, 0x4(r27)
            stw     r21, addend
        }
        offset = offset ^ 0x17;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION isAnimLooped__Q28mintglue17Scn__Title__CharaFv
bool Scn__Title__Chara::isAnimLooped() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 unused;
    volatile u32 response;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xF43D0A92
        opword  0x645D6A91
        opword  MF_WORD(0x30)
        opword  0x946CC080
        opword  0xF85BB480
    after1:
        mflr    r21
        lwz     r20, 0x0(r21)
        add     r20, r20, r21
        lwz     r24, 0xC(r21)
        stw     r20, start
        add     r24, r24, r20
        stw     r24, end
    }
    hash = 0x811C9E53;
    last = end;
    word = start;
    for (; word != last; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    hash += hash << 13;
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x588766B7
    after2:
        mflr    r24
        lwz     r18, 0x0(r24)
        stw     r18, expected
    }
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash -= expected;
    if (hash == 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xE0)
            opword  0x00E40680
            opword  0xA47AA393
            opword  0x20F2C392
        after3:
            mflr    r21
            addi    r20, r21, 0x1C
            mtlr    r20
            lwz     r17, 0x0(r21)
            stw     r17, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r21, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x114)
            opword  0xAF471F09
            opword  0x4427D580
            opword  MF_WORD(0x120)
        after4:
            mflr    r29
            lwz     r16, 0xC(r29)
            stw     r16, unused
            lwz     r16, 0x0(r29)
            stw     r29, base
            stw     r16, offset
        }
        offset = offset - 0x3C;
        unused = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        return mChara->isAnimLooped();
    }
}
#undef MF_FUNCTION

void Scn__Title__Chara::effectRequestN(u32 index, const char* name) {
    mChara->effectRequestN(index, name);
}

}
