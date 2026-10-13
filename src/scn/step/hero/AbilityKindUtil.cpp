#include "scn/step/hero/AbilityKindUtil.h"

#include "metafortress.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

namespace {

const pause::ManualKind T_MANUAL_KIND_TABLE[] = {
    pause::MANUAL_KIND_NORMAL,      pause::MANUAL_KIND_SWORD,      pause::MANUAL_KIND_CUTTER,     pause::MANUAL_KIND_LEAF,
    pause::MANUAL_KIND_WHIP,        pause::MANUAL_KIND_FIRE,       pause::MANUAL_KIND_NEEDLE,     pause::MANUAL_KIND_BEAM,
    pause::MANUAL_KIND_SPARK,       pause::MANUAL_KIND_STONE,      pause::MANUAL_KIND_SLEEP,      pause::MANUAL_KIND_PARASOL,
    pause::MANUAL_KIND_WATER,       pause::MANUAL_KIND_HIGHJUMP,   pause::MANUAL_KIND_TORNADO,    pause::MANUAL_KIND_BOMB,
    pause::MANUAL_KIND_SPEAR,       pause::MANUAL_KIND_HAMMER,     pause::MANUAL_KIND_ICE,        pause::MANUAL_KIND_WING,
    pause::MANUAL_KIND_NINJA,       pause::MANUAL_KIND_FIGHTER,    pause::MANUAL_KIND_CRASH,      pause::MANUAL_KIND_MIKE,
    pause::MANUAL_KIND_LANDIA,      pause::MANUAL_KIND_SUPER_SWORD, pause::MANUAL_KIND_SUPER_FIRE, pause::MANUAL_KIND_SUPER_BEAM,
    pause::MANUAL_KIND_SUPER_HAMMER, pause::MANUAL_KIND_SUPER_ICE, pause::MANUAL_KIND_MIKE,       pause::MANUAL_KIND_MIKE,
    pause::MANUAL_KIND_META,        pause::MANUAL_KIND_DEDEDE,     pause::MANUAL_KIND_DEE,
};

const char* T_FDN_NAME_TABLE[] = {
    "StepHrAbKirbyNormal.dn",     "StepHrAbKirbySword.dn",       "StepHrAbKirbyCutter.dn",    "StepHrAbKirbyLeaf.dn",
    "StepHrAbKirbyWhip.dn",       "StepHrAbKirbyFire.dn",        "StepHrAbKirbyNeedle.dn",    "StepHrAbKirbyBeam.dn",
    "StepHrAbKirbySpark.dn",      "StepHrAbKirbyStone.dn",       "StepHrAbKirbySleep.dn",     "StepHrAbKirbyParasol.dn",
    "StepHrAbKirbyWater.dn",      "StepHrAbKirbyHighjump.dn",    "StepHrAbKirbyTornado.dn",   "StepHrAbKirbyBomb.dn",
    "StepHrAbKirbySpear.dn",      "StepHrAbKirbyHammer.dn",      "StepHrAbKirbyIce.dn",       "StepHrAbKirbyWing.dn",
    "StepHrAbKirbyNinja.dn",      "StepHrAbKirbyFighter.dn",     "StepHrAbKirbyCrash.dn",     "StepHrAbKirbyMike.dn",
    "StepHrAbKirbyLandia.dn",     "StepHrAbKirbySuperSword.dn",  "StepHrAbKirbySuperFire.dn", "StepHrAbKirbySuperBeam.dn",
    "StepHrAbKirbySuperHammer.dn", "StepHrAbKirbySuperIce.dn",   "StepHrAbKirbyMike.dn",      "StepHrAbKirbyMike.dn",
    "StepHrAbMeta.dn",            "StepHrAbDedede.dn",           "StepHrAbDee.dn",
};

}

const char* AbilityKindUtil::FDNName(AbilityKind kind) {
    return T_FDN_NAME_TABLE[kind];
}

bool AbilityKindUtil::IsSuper(AbilityKind kind) {
    return static_cast<u32>(kind - ABILITY_KIND_SUPER_SWORD) <= ABILITY_KIND_SUPER_ICE - ABILITY_KIND_SUPER_SWORD;
}

#define MF_FUNCTION IsKirbyAbility__Q43scn4step4hero15AbilityKindUtilFQ43scn4step4hero11AbilityKind
bool AbilityKindUtil::IsKirbyAbility(AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 hash;
    u32 i;
    u32 base;
    u32 limit;

    hash = 0xBF;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x601ADF90
        opword  0xF8954290
        opword  MF_WORD(0x34)
        opword  0x1E027802
    after1:
        mflr    r14
        lwz     r16, 0x0(r14)
        add     r16, r16, r14
        stw     r16, start
        lwz     r29, 0xc(r14)
        add     r16, r16, r29
        stw     r16, end
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    for (; i != limit; i += 2) {
        hash = (hash << 4) ^ (hash >> 28);
        hash ^= *(u16*)(base + i - 1);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    asm {
        bl      after2
        opword  MF_WORD(0xB0)
        opword  0x12C438BA
    after2:
        mflr    r17
        lwz     r22, 0x0(r17)
        stw     r22, expected
    }
    switch (kind) {
    case ABILITY_KIND_META:
    case ABILITY_KIND_DEDEDE:
    case ABILITY_KIND_DEE:
        return expected != hash;
    default:
        return expected == hash;
    }
}
#undef MF_FUNCTION

pause::ManualKind AbilityKindUtil::ToManualKind(AbilityKind kind, bool a, bool b) {
    pause::ManualKind result = T_MANUAL_KIND_TABLE[kind];
    if (result == pause::MANUAL_KIND_NORMAL && (a || b)) {
        result = pause::MANUAL_KIND_1;
    }
    return result;
}

}
}
}
