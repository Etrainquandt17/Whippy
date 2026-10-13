#include "scn/step/ChallengeKindUtil.h"

#include "metafortress.h"

// TODO: replace with the standard library header once the game code has one.
extern "C" int sprintf(char* str, const char* format, ...);

namespace scn {
namespace step {

namespace {

struct Info {
    hero::AbilityKind abilityKind;
    const char* challengeName;
    const char* abilityName;
    map::Kind mapKind;
    u32 portalNo;
};

// TODO: name the maps and the two kinds that are not in their enums.
const hero::AbilityKind ABILITY_KIND_NONE = static_cast<hero::AbilityKind>(0x23);
const map::Kind MAP_KIND_NONE = static_cast<map::Kind>(0x2B8);

const Info T_INFOS[CHALLENGE_KIND_NUM] = {
    {hero::ABILITY_KIND_SWORD, "Sword", "Sword", static_cast<map::Kind>(0), 6},
    {ABILITY_KIND_NONE, 0, 0, MAP_KIND_NONE, 0xFFFFFFFF},
    {hero::ABILITY_KIND_WHIP, "Whip", "Whip", static_cast<map::Kind>(4), 8},
    {hero::ABILITY_KIND_WATER, "Water", "Water", static_cast<map::Kind>(8), 9},
    {ABILITY_KIND_NONE, 0, 0, MAP_KIND_NONE, 0xFFFFFFFF},
    {hero::ABILITY_KIND_BOMB, "Bomb", "Bomb", static_cast<map::Kind>(0xC), 0xB},
    {hero::ABILITY_KIND_WING, "Wing", "Wing", static_cast<map::Kind>(0xF), 0xC},
    {hero::ABILITY_KIND_NORMAL, "Carry", "Normal", static_cast<map::Kind>(0x13), 0x11},
    {ABILITY_KIND_NONE, 0, 0, MAP_KIND_NONE, 0xFFFFFFFF},
    {hero::ABILITY_KIND_HIGHJUMP, "Highjump", "Highjump", static_cast<map::Kind>(0x19), 0x12},
};

#define MF_FUNCTION t_info__Q33scn4step35_unnamed_ChallengeKindUtil_prt_cpp_FQ33scn4step13ChallengeKind
Info t_info(ChallengeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  MF_WORD(0x24)
    after1:
        mflr    r18
        lwz     r16, 0x0(r18)
        lwz     r24, 0x4(r18)
        add     r16, r16, r18
        add     r24, r24, r16
        stw     r16, start
        stw     r24, end
        bl      after2
        opword  MF_WORD(0x48)
        opword  0x4F59ECF8
    after2:
        mflr    r15
        lwz     r17, 0x0(r15)
        stw     r17, expected
    }
    hash = 0;
    i = 1;
    last = end;
    limit = last - start + 1;
    last--;
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    while (hash - expected != 0) {
    }
    return T_INFOS[kind];
}
#undef MF_FUNCTION

}

hero::AbilityKind ChallengeKindUtil::AbilityKind(ChallengeKind kind) {
    return t_info(kind).abilityKind;
}

ChallengeKind ChallengeKindUtil::AbilityKindToChallengeKind(hero::AbilityKind kind) {
    for (int i = 0; i < CHALLENGE_KIND_NUM; i++) {
        if (kind == t_info(static_cast<ChallengeKind>(i)).abilityKind) {
            return static_cast<ChallengeKind>(i);
        }
    }
    return CHALLENGE_KIND_NUM;
}

#define MF_FUNCTION TutorialDNPath__Q33scn4step17ChallengeKindUtilFQ33scn4step13ChallengeKind
hel::common::FixedString<64> ChallengeKindUtil::TutorialDNPath(ChallengeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;

    asm {
        bl      after1
        opword  0x7B6EED06
        opword  0xCC8B0280
        opword  MF_WORD(0x30)
        opword  0x95CDAB09
        opword  0x888CDA91
        opword  MF_WORD(0x3C)
        opword  0x70559A05
    after1:
        mflr    r29
        lwz     r22, 0x8(r29)
        lwz     r23, 0x14(r29)
        stw     r23, end
        stw     r22, start
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0xEA7F55F0
    after2:
        mflr    r18
        lwz     r15, 0x0(r18)
        stw     r15, expected
    }
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    if (hash != limit) {
        volatile u32 anchor;
        volatile u32 offset;
        volatile u32 response;
        volatile u32 unused;

        asm {
            bl      after3
            opword  MF_WORD(0xDC)
        after3:
            mflr    r20
            lwz     r29, 0x0(r20)
            stw     r29, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r29, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r29
            bl      after4
            opword  MF_WORD(0x100)
            opword  0x6DC02209
            opword  MF_WORD(0x108)
        after4:
            mflr    r23
            stw     r23, anchor
            lwz     r14, 0x0(r23)
            stw     r14, offset
            lwz     r27, 0x8(r23)
            stw     r27, unused
        }
        offset = offset - 0x21;
        unused = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else {
        return hel::common::FixedString<64>::FromFormat("Challengetutorial%s.dn", ChallengeName(kind));
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION ChallengeName__Q33scn4step17ChallengeKindUtilFQ33scn4step13ChallengeKind
const char* ChallengeKindUtil::ChallengeName(ChallengeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 anchor;
    volatile u32 offset;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;
    ChallengeKind k;

    k = kind;
    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x147754B6
    after1:
        mflr    r30
        lwz     r15, 0x0(r30)
        stw     r15, expected
        bl      after2
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
    after2:
        mflr    r16
        lwz     r17, 0x0(r16)
        lwz     r14, 0x4(r16)
        add     r17, r17, r16
        add     r14, r14, r17
        stw     r17, start
        stw     r14, end
    }
    limit = end - start + 1;
    last = end;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x1000181;
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    if (hash == limit) {
        return t_info(k).challengeName;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xE0)
    after3:
        mflr    r26
        lwz     r14, 0x0(r26)
        stw     r14, -0x4(r1)
        stw     r26, 0x0(r1)
        stw     r14, -0x4(r1)
        stw     r26, -0x8(r1)
        mtlr    r14
        bl      after4
        opword  MF_WORD(0x104)
        opword  0xE9B9AB0D
        opword  MF_WORD(0x10C)
    after4:
        mflr    r19
        stw     r19, anchor
        lwz     r26, 0x0(r19)
        stw     r26, offset
        lwz     r16, 0x8(r19)
        stw     r16, addend
    }
    offset = offset ^ 0xD3;
    response = offset + addend;
    response = response + anchor;
    asm {
        lwz     r18, response
        mtlr    r18
        blr
    }
}
#undef MF_FUNCTION

const char* ChallengeKindUtil::AbilityName(ChallengeKind kind) {
    return t_info(kind).abilityName;
}

map::Kind ChallengeKindUtil::MapKind(ChallengeKind kind) {
    return t_info(kind).mapKind;
}

u32 ChallengeKindUtil::PortalNo(ChallengeKind kind) {
    return t_info(kind).portalNo;
}

#define MF_FUNCTION ToChallengeKind__Q33scn4step17ChallengeKindUtilFQ43scn4step3map4Kind
ChallengeKind ChallengeKindUtil::ToChallengeKind(map::Kind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 mask;
    volatile u32 anchor;
    volatile u32 offset;
    map::Kind k;
    u32 t;
    u32 a;
    u32 x;
    u32 word;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x14E36191
        opword  MF_WORD(0x2C)
        opword  0xA7F1290B
        opword  0xF84B2481
    after1:
        mflr    r26
        lwz     r21, 0x0(r26)
        lwz     r25, 0x8(r26)
        add     r21, r21, r26
        add     r25, r25, r21
        stw     r21, start
        stw     r25, end
    }
    limit = end;
    word = start;
    hash = 0xB3;
    for (;;) {
        if (word == limit) {
            break;
        }
        x = *(u16*)word;
        a = hash << 4;
        t = hash >> 28;
        t = a ^ t;
        hash = x ^ t;
        word += 2;
    }
    t = hash << 3;
    hash += t;
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x9D8C03B9
    after2:
        mflr    r28
        lwz     r24, 0x0(r28)
        stw     r24, expected
    }
    t = hash >> 11;
    hash ^= t;
    t = hash << 15;
    hash += t;
    t = expected;
    hash ^= t;
    if (hash == 0) {
        k = kind;
        if (0 <= k && k <= 3) {
            return CHALLENGE_KIND_SWORD;
        }
        if (4 <= k && k <= 7) {
            return CHALLENGE_KIND_WHIP;
        }
        if (8 <= k && k <= 0xB) {
            return CHALLENGE_KIND_WATER;
        }
        if (0xC <= k && k <= 0xE) {
            return CHALLENGE_KIND_BOMB;
        }
        if (0xF <= k && k <= 0x12) {
            return CHALLENGE_KIND_WING;
        }
        if (0x19 <= k && k <= 0x1C) {
            return CHALLENGE_KIND_HIGHJUMP;
        }
        if (0x13 <= k && k <= 0x18) {
            return CHALLENGE_KIND_CARRY;
        }
        return CHALLENGE_KIND_NUM;
    }
    asm {
        bl      after3
        opword  0xADA4A308
        opword  0xF8684009
        opword  MF_WORD(0x180)
    after3:
        mflr    r15
        lwz     r17, 0x8(r15)
        stw     r17, -0x4(r1)
        stw     r15, 0x0(r1)
        stw     r17, -0x4(r1)
        stw     r15, -0x8(r1)
        mtlr    r17
        bl      after4
        opword  MF_WORD(0x1A4)
        opword  0xC4C66393
        opword  0xB09D5081
        opword  MF_WORD(0x1B0)
    after4:
        mflr    r18
        lwz     r15, 0x0(r18)
        stw     r18, anchor
        lwz     r16, 0xc(r18)
        stw     r15, offset
        stw     r16, mask
    }
    offset = offset ^ 0xCA;
    response = offset ^ mask;
    response = response + anchor;
    asm {
        lwz     r28, response
        mtlr    r28
        blr
    }
}
#undef MF_FUNCTION

bool ChallengeKindUtil::IsChallengePortal(u32 portalNo) {
    for (int i = 0; i < CHALLENGE_KIND_NUM; i++) {
        if (portalNo == t_info(static_cast<ChallengeKind>(i)).portalNo) {
            return true;
        }
    }
    return false;
}

ChallengeKind ChallengeKindUtil::PortalToChallengeKind(u32 portalNo) {
    for (int i = 0; i < CHALLENGE_KIND_NUM; i++) {
        if (portalNo == t_info(static_cast<ChallengeKind>(i)).portalNo) {
            return static_cast<ChallengeKind>(i);
        }
    }
    return CHALLENGE_KIND_NUM;
}

SphereUnlockKind ChallengeKindUtil::ToSphereUnlockKind(ChallengeKind kind) {
    switch (kind) {
    case CHALLENGE_KIND_SWORD:
        return SPHERE_UNLOCK_KIND_0;
    case CHALLENGE_KIND_WHIP:
        return SPHERE_UNLOCK_KIND_1;
    case CHALLENGE_KIND_WATER:
        return SPHERE_UNLOCK_KIND_2;
    case CHALLENGE_KIND_BOMB:
        return SPHERE_UNLOCK_KIND_4;
    case CHALLENGE_KIND_WING:
        return SPHERE_UNLOCK_KIND_3;
    case CHALLENGE_KIND_HIGHJUMP:
        return SPHERE_UNLOCK_KIND_5;
    case CHALLENGE_KIND_CARRY:
        return SPHERE_UNLOCK_KIND_6;
    default:
        // TODO: 13 is probably the number of kinds; SphereUnlockKind.h names seven.
        return static_cast<SphereUnlockKind>(0xD);
    }
}

ChallengeKind ChallengeKindUtil::SphereUnlockKindToChallengeKind(SphereUnlockKind kind) {
    switch (kind) {
    case SPHERE_UNLOCK_KIND_0:
        return CHALLENGE_KIND_SWORD;
    case SPHERE_UNLOCK_KIND_1:
        return CHALLENGE_KIND_WHIP;
    case SPHERE_UNLOCK_KIND_2:
        return CHALLENGE_KIND_WATER;
    case SPHERE_UNLOCK_KIND_4:
        return CHALLENGE_KIND_BOMB;
    case SPHERE_UNLOCK_KIND_3:
        return CHALLENGE_KIND_WING;
    case SPHERE_UNLOCK_KIND_5:
        return CHALLENGE_KIND_HIGHJUMP;
    case SPHERE_UNLOCK_KIND_6:
        return CHALLENGE_KIND_CARRY;
    default:
        return CHALLENGE_KIND_NUM;
    }
}

lyt::LayoutContext ChallengeKindUtil::TitleLayoutContext(ChallengeKind kind, mem::IAllocator& allocator) {
    const char* name = ChallengeName(kind);
    char path[0x30];
    char file[0x18];
    sprintf(path, "step/challenge/Title%s", name);
    sprintf(file, "Title%s", name);
    return lyt::LayoutContext(path, file, allocator);
}

}
}
