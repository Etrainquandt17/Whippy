#include "scn/step/hero/FormationUtil.h"

#include "hel/common/MutableArray.h"
#include "metafortress.h"

using hel::common::Array;
using hel::common::MutableArray;

// TODO: this unit calls its own functions where the compiler would inline them by itself.
#pragma auto_inline off

namespace scn {
namespace step {
namespace hero {

namespace {

#define MF_FUNCTION isDefaultPosKind__Q43scn4step4hero31_unnamed_FormationUtil_prt_cpp_FQ43scn4step4hero4Kind
bool isDefaultPosKind(Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;

    asm {
        bl      ranged
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0x088B0F90
    ranged:
        mflr    r19
        lwz     r16, 0x0(r19)
        add     r16, r16, r19
        stw     r16, start
        lwz     r14, 0x4(r19)
        add     r16, r16, r14
        stw     r16, end
        bl      stored
        opword  MF_WORD(0x50)
        opword  0xC818D57A
    stored:
        mflr    r21
        lwz     r28, 0x0(r21)
        stw     r28, expected
        li      r29, 0x1
        lwz     r25, start
        lwz     r27, end
        subf    r27, r25, r27
        addi    r24, r27, 0x1
        li      r31, 0x0
    next:
        cmplw   cr4, r29, r24
        beq     cr4, summed
        mulli   r31, r31, 0x6b
        add     r27, r25, r29
        lhz     r27, -0x1(r27)
        add     r31, r31, r27
        addi    r29, r29, 0x2
        b       next
    summed:
        slwi    r27, r31, 3
        add     r31, r31, r27
        srwi    r27, r31, 11
        xor     r31, r31, r27
        slwi    r27, r31, 15
        add     r31, r31, r27
        lwz     r27, expected
        andc    r27, r31, r27
        lwz     r29, expected
        andc    r29, r29, r31
        or      r29, r27, r29
        cntlzw  r31, r29
        srwi    r29, r31, 5
        srwi    r31, r29, 1
        subf    r31, r31, r29
        cmpwi   cr4, r31, 0x0
        bne     cr4, intact
        bl      smashed
        opword  0xB01C1090
        opword  MF_WORD(0xE8)
    smashed:
        mflr    r26
        lwz     r21, 0x4(r26)
        stw     r21, -0x4(r1)
        stw     r26, 0x0(r1)
        stw     r21, -0x4(r1)
        stw     r26, -0x8(r1)
        mtlr    r21
        bl      located
        opword  MF_WORD(0x10C)
        opword  0x09BE6802
        opword  MF_WORD(0x114)
    located:
        mflr    r22
        lwz     r19, 0x0(r22)
        lwz     r21, 0x8(r22)
        stw     r21, key
        stw     r19, offset
        stw     r22, base
    }
    offset = offset - 0xE0;
    response = offset ^ key;
    response = response + base;
    asm {
        lwz     r22, response
        mtlr    r22
        blr
    }
    goto done;
intact:
    switch (kind) {
    case 0:
    case 4:
    case 5:
    case 6:
        return true;
    default:
        return false;
    }
done:;
}
#undef MF_FUNCTION

#define MF_FUNCTION defaultPosKind__Q43scn4step4hero31_unnamed_FormationUtil_prt_cpp_FQ43scn4step4hero4Kind
WarpStarRidePosKind defaultPosKind(Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 size;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0x60FC66F6
    after1:
        mflr    r29
        lwz     r24, 0x0(r29)
        stw     r24, expected
    }
    hash = 0x811C9E29;
    asm {
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x74348991
        opword  0xBEB38B0A
        opword  MF_WORD(0x48)
        opword  0xD49E3181
        opword  0x481DD807
    after2:
        mflr    r24
        lwz     r22, 0xc(r24)
        lwz     r21, 0x0(r24)
        add     r21, r21, r24
        stw     r21, start
        add     r22, r22, r21
        stw     r22, end
    }
    size = end - start;
    base = start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001AB;
    }
    switch (kind) {
    case 0:
        return WarpStarRidePosKind(0);
    case 4:
        return WarpStarRidePosKind(2);
    case 5:
        return WarpStarRidePosKind(3);
    case 6:
        return WarpStarRidePosKind(1);
    default:
        while (hash - expected != 0) {
        }
        return WarpStarRidePosKind(0);
    }
}
#undef MF_FUNCTION

}

#define MF_FUNCTION GetWarpStarRidePosKind__Q43scn4step4hero13FormationUtilFRCQ33hel6common30Array_Q43scn4step4hero4Kind_4_Ul
WarpStarRidePosKind FormationUtil::GetWarpStarRidePosKind(const Array<Kind, 4>& kinds, u32 index) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0xBF;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x65450907
    after1:
        mflr    r19
        lwz     r18, 0x0(r19)
        add     r18, r18, r19
        stw     r18, start
        bl      after2
        opword  0x8667E40B
        opword  0x88226880
        opword  MF_WORD(0x48)
        opword  0x90C68D80
    after2:
        mflr    r19
        lwz     r24, 0x8(r19)
        add     r18, r18, r24
        stw     r18, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    asm {
        bl      after3
        opword  MF_WORD(0x7C)
        opword  0xF54B1421
    after3:
        mflr    r28
        lwz     r27, 0x0(r28)
        stw     r27, expected
    }
    for (; i != limit; i += 2) {
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(last - 1 - i);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || isDefaultPosKind(kinds[index])) {
        return defaultPosKind(kinds[index]);
    }
    MutableArray<WarpStarRidePosKind, 4> used;
    for (u32 k = 0; k < 4; k++) {
        if (k != index && isDefaultPosKind(kinds[k])) {
            used.add(defaultPosKind(kinds[k]));
        }
    }
    for (u32 k = 0; k < 4; k++) {
        if (!isDefaultPosKind(kinds[k])) {
            WarpStarRidePosKind pos = WarpStarRidePosKind(3);
            for (u32 p = 0; p < 4; p++) {
                pos = WarpStarRidePosKind(p);
                bool found = false;
                for (u32 j = 0; j < used.count(); j++) {
                    if (pos == used[j]) {
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    if (k == index) {
                        return pos;
                    }
                    used.add(pos);
                    break;
                }
            }
        }
    }
    while (hash - expected != 0) {
    }
    return WarpStarRidePosKind(0);
}
#undef MF_FUNCTION

}}}  // namespace scn::step::hero
