#include "scn/goalgame/desc/hero/HeroDesc.h"

#include "metafortress.h"

// TODO: these come from a header of the goal game that does not exist yet.
namespace scn {
namespace goalgame {

static f32 ONE_DPF(f32 value) {
    return value / 16.0f;
}

static const f32 FALL_ACL = ONE_DPF(-0.25f);
static const f32 PUSH2_YPOS = ONE_DPF(-90.0f);
static const f32 PUSHDOWN_YPOS = ONE_DPF(40.0f);

}}  // namespace scn::goalgame

using namespace scn::step::hero;

namespace scn {
namespace goalgame {
namespace desc {
namespace hero {

#define MF_FUNCTION Model__Q53scn8goalgame4desc4hero8HeroDescFQ33scn8goalgame10GGHeroKind
const modeldesc::ModelDesc& HeroDesc::Model(GGHeroKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    u32 hash;
    u32 word;
    u32 last;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
    after1:
        mflr    r20
        lwz     r22, 0x0(r20)
        add     r22, r22, r20
        stw     r22, start
        bl      after2
        opword  MF_WORD(0x44)
        opword  0x9497C490
    after2:
        mflr    r20
        lwz     r15, 0x0(r20)
        add     r22, r22, r15
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
        hash *= 0x01000181;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    asm {
        bl      after3
        opword  MF_WORD(0xA0)
        opword  0x03C1A122
    after3:
        mflr    r28
        lwz     r27, 0x0(r28)
        stw     r27, expected
    }
    hash ^= expected;
    if (hash == 0) {
        switch (kind) {
        case GG_HERO_KIND_META:
            return modeldesc::Meta::Model();
        case GG_HERO_KIND_DEDEDE:
            return modeldesc::Dedede::Model();
        case GG_HERO_KIND_DEE:
            return modeldesc::Dee::Model();
        default:
            return modeldesc::Kirby::Model();
        }
    } else {
        asm {
            bl      after4
            opword  0x2C6C2A90
            opword  0x50DB4F92
            opword  0x4C61AF93
            opword  MF_WORD(0x118)
        after4:
            mflr    r14
            lwz     r17, 0xc(r14)
            stw     r17, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r17
            bl      after5
            opword  MF_WORD(0x13C)
            opword  MF_WORD(0x140)
        after5:
            mflr    r15
            lwz     r17, 0x0(r15)
            stw     r15, base
            lwz     r20, 0x4(r15)
            stw     r17, offset
            stw     r20, key
        }
        offset = offset + 0xF6;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION Anim__Q53scn8goalgame4desc4hero8HeroDescFQ33scn8goalgame10GGHeroKind
const modeldesc::AnimDesc& HeroDesc::Anim(GGHeroKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 key;
    u32 size;
    u32 i;
    u32 first;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x793E6185
    after1:
        mflr    r24
        lwz     r21, 0x0(r24)
        stw     r21, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x646AE691
        opword  0x0960A50C
        opword  MF_WORD(0x48)
        opword  0x45DC4903
    after2:
        mflr    r21
        lwz     r30, 0x0(r21)
        lwz     r18, 0xc(r21)
        add     r30, r30, r21
        add     r18, r18, r30
        stw     r30, start
        stw     r18, end
    }
    hash = 0;
    first = start;
    size = end - first;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash *= 61;
        hash += *(u16*)(first + i - 1);
    }
    hash ^= expected;
    if (hash == 0) {
        switch (kind) {
        case GG_HERO_KIND_META:
            return modeldesc::Meta::Anim();
        case GG_HERO_KIND_DEDEDE:
            return modeldesc::Dedede::Anim();
        case GG_HERO_KIND_DEE:
            return modeldesc::Dee::Anim();
        default:
            return modeldesc::Kirby::Anim();
        }
    } else {
        asm {
            stw     r21, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x100)
            opword  0x1D54C305
            opword  0x8410200A
            opword  0xF0F3AC90
        after3:
            mflr    r21
            lwz     r28, 0x0(r21)
            stw     r28, 0x0(r1)
            stw     r21, 0x4(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x128)
            opword  0x68021092
            opword  0x44570892
            opword  MF_WORD(0x134)
        after4:
            mflr    r14
            lwz     r24, 0x0(r14)
            lwz     r17, 0xc(r14)
            stw     r17, key
            stw     r24, offset
            stw     r14, base
        }
        offset = offset ^ 0x4E;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION ModelPath__Q53scn8goalgame4desc4hero8HeroDescFQ33scn8goalgame10GGHeroKind
const char* HeroDesc::ModelPath(GGHeroKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 hash;
    u32 i;
    u32 limit;
    GGHeroKind index;
    static const char* modelPath[] = {
        "step/chara/hero/kirby/base/Pink",
        "step/chara/hero/kirby/base/Yellow",
        "step/chara/hero/kirby/base/Blue",
        "step/chara/hero/kirby/base/Green",
        "step/chara/hero/meta/base/Default",
        "step/chara/hero/dedede/base/Default",
        "step/chara/hero/dee/base/Default",
    };

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x0CD9F235
    after1:
        mflr    r29
        lwz     r21, 0x0(r29)
        stw     r21, expected
        bl      after2
        opword  0xCC5A6780
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0x32071B0A
        opword  0x44787291
    after2:
        mflr    r28
        lwz     r24, 0x4(r28)
        stw     r24, end
        lwz     r24, 0x8(r28)
        stw     r24, start
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    last--;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x01000181;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    while (hash - expected != 0) {
    }
    index = GG_HERO_KIND_KIRBY_PINK;
    switch (kind) {
    case GG_HERO_KIND_KIRBY_PINK:
    case GG_HERO_KIND_KIRBY_YELLOW:
    case GG_HERO_KIND_KIRBY_BLUE:
    case GG_HERO_KIND_KIRBY_GREEN:
    case GG_HERO_KIND_META:
    case GG_HERO_KIND_DEDEDE:
    case GG_HERO_KIND_DEE:
        index = kind;
        break;
    }
    return modelPath[index];
}
#undef MF_FUNCTION

const char* HeroDesc::AnimPath(GGHeroKind kind) {
    GGHeroKind index;
    static const char* animPath[] = {
        "step/chara/hero/kirby/normal/Motion",
        "step/chara/hero/kirby/normal/Motion",
        "step/chara/hero/kirby/normal/Motion",
        "step/chara/hero/kirby/normal/Motion",
        "step/chara/hero/meta/normal/Motion",
        "step/chara/hero/dedede/normal/Motion",
        "step/chara/hero/dee/normal/Motion",
    };

    index = GG_HERO_KIND_KIRBY_PINK;
    switch (kind) {
    case GG_HERO_KIND_KIRBY_PINK:
    case GG_HERO_KIND_KIRBY_YELLOW:
    case GG_HERO_KIND_KIRBY_BLUE:
    case GG_HERO_KIND_KIRBY_GREEN:
    case GG_HERO_KIND_META:
    case GG_HERO_KIND_DEDEDE:
    case GG_HERO_KIND_DEE:
        index = kind;
        break;
    }
    return animPath[index];
}

}}}}  // namespace scn::goalgame::desc::hero
