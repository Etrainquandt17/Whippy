#include "scn/step/map/KindUtil.h"

#include "metafortress.h"
#include "scn/step/StageKindUtil.h"

namespace scn {
namespace step {
namespace map {

#define MF_FUNCTION IsFinalStageMap__Q43scn4step3map8KindUtilFQ43scn4step3map4Kind
bool KindUtil::IsFinalStageMap(Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    bool result;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xA05B4B80
        opword  0x14816980
    after1:
        mflr    r26
        lwz     r20, 0x0(r26)
        add     r20, r20, r26
        stw     r20, start
        bl      after2
        opword  0x406FAD80
        opword  0x34028480
        opword  MF_WORD(0x4C)
        opword  0x2809060E
        opword  0xC1707301
    after2:
        mflr    r26
        lwz     r19, 0x8(r26)
        add     r20, r20, r19
        stw     r20, end
    }
    word = start;
    last = end;
    hash = 0;
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
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after3
        opword  MF_WORD(0xB4)
        opword  0xF810AB42
    after3:
        mflr    r27
        lwz     r21, 0x0(r27)
        stw     r21, expected
    }
    hash += hash << 15;
    // The stored word is the complement of the sum, so this hangs when they are equal.
    while (hash - expected == 0) {
    }
    result = false;
    if (IsStageMap(kind) && StageKindUtil::IsFinalStage(ToStageKind(kind))) {
        result = true;
    }
    return result;
}
#undef MF_FUNCTION

u32 KindUtil::ToStageIndex(Kind kind) {
    return ToStageIndex(ToStageKind(kind));
}

#define MF_FUNCTION ToStageIndex__Q43scn4step3map8KindUtilFQ33scn4step9StageKind
u32 KindUtil::ToStageIndex(StageKind stage) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x2F4C5BF1
    after1:
        mflr    r22
        lwz     r19, 0x0(r22)
        stw     r19, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x08B9BB80
        opword  0x68788C93
        opword  MF_WORD(0x48)
    after2:
        mflr    r22
        lwz     r25, 0xc(r22)
        stw     r25, end
        lwz     r19, 0x0(r22)
        stw     r19, start
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x01000193;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    switch (stage) {
    case STAGE_KIND_0:
    case STAGE_KIND_5:
    case STAGE_KIND_10:
    case STAGE_KIND_15:
    case STAGE_KIND_21:
    case STAGE_KIND_27:
    case STAGE_KIND_33:
        return 0;
    case STAGE_KIND_1:
    case STAGE_KIND_6:
    case STAGE_KIND_11:
    case STAGE_KIND_16:
    case STAGE_KIND_22:
    case STAGE_KIND_28:
    case STAGE_KIND_34:
        return 1;
    case STAGE_KIND_2:
    case STAGE_KIND_7:
    case STAGE_KIND_12:
    case STAGE_KIND_17:
    case STAGE_KIND_23:
    case STAGE_KIND_29:
    case STAGE_KIND_35:
        return 2;
    case STAGE_KIND_3:
    case STAGE_KIND_8:
    case STAGE_KIND_13:
    case STAGE_KIND_18:
    case STAGE_KIND_24:
    case STAGE_KIND_30:
    case STAGE_KIND_36:
        return 3;
    case STAGE_KIND_4:
    case STAGE_KIND_9:
    case STAGE_KIND_14:
    case STAGE_KIND_19:
    case STAGE_KIND_25:
    case STAGE_KIND_31:
    case STAGE_KIND_37:
        return 4;
    case STAGE_KIND_20:
    case STAGE_KIND_26:
    case STAGE_KIND_32:
    case STAGE_KIND_38:
        return 5;
    default:
        while (hash - expected != 0) {
        }
        return ToStageIndex(KIND_0);
    }
}
#undef MF_FUNCTION

}
}
}
