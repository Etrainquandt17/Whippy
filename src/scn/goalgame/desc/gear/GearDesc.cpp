#include "scn/goalgame/desc/gear/GearDesc.h"

#include "metafortress.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"

using namespace scn::step::hero;

namespace scn {
namespace goalgame {
namespace desc {
namespace gear {

#define MF_FUNCTION isUseGear__Q53scn8goalgame4desc4gear8GearDescFQ43scn4step4hero11AbilityKind
bool GearDesc::isUseGear(AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    bool result;
    u32 base;
    u32 last;
    u32 limit;
    u32 hash;

    result = false;
    asm {
        bl      after1
        opword  0x64052F90
        opword  0xB002750E
        opword  MF_WORD(0x28)
        opword  0x78CCBF93
        opword  MF_WORD(0x30)
    after1:
        mflr    r24
        lwz     r26, 0x8(r24)
        lwz     r27, 0x10(r24)
        stw     r26, end
        stw     r27, start
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0x2A52E04B
    after2:
        mflr    r16
        lwz     r27, 0x0(r16)
        stw     r27, expected
    }
    hash = 0;
    base = last - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 61;
        hash += *(u16*)(base - i);
        i += 2;
    }
    switch (kind) {
    case ABILITY_KIND_SWORD:
    case ABILITY_KIND_WHIP:
    case ABILITY_KIND_BEAM:
    case ABILITY_KIND_PARASOL:
    case ABILITY_KIND_SPEAR:
    case ABILITY_KIND_HAMMER:
        result = expected == hash;
        break;
    }
    return result;
}
#undef MF_FUNCTION

bool GearDesc::isUseModel(AbilityKind kind) {
    bool result = false;
    switch (kind) {
    case ABILITY_KIND_SWORD:
    case ABILITY_KIND_WHIP:
    case ABILITY_KIND_BEAM:
    case ABILITY_KIND_PARASOL:
    case ABILITY_KIND_SPEAR:
    case ABILITY_KIND_HAMMER:
        result = true;
        break;
    }
    return result;
}

const gobj::GearAnimDesc& GearDesc::Anim(AbilityKind kind) {
    static gobj::GearAnimDesc desc;
    desc._0 = 0;
    desc._4 = 0;
    switch (kind) {
    case ABILITY_KIND_SWORD:
        return modeldesc::Sword::SwordAnim();
    case ABILITY_KIND_WHIP:
        return modeldesc::Whip::WhipAnim();
    case ABILITY_KIND_BEAM:
        return modeldesc::Beam::StickAnim();
    case ABILITY_KIND_PARASOL:
        return modeldesc::Parasol::ParasolAnim();
    case ABILITY_KIND_SPEAR:
        return modeldesc::Spear::SpearAnim();
    case ABILITY_KIND_HAMMER:
        return modeldesc::Hammer::HammerAnim();
    }
    return desc;
}

const gobj::GearModelDesc& GearDesc::Model(AbilityKind kind) {
    switch (kind) {
    case ABILITY_KIND_SWORD:
        return modeldesc::Sword::SwordModel();
    case ABILITY_KIND_WHIP:
        return modeldesc::Whip::WhipModel();
    case ABILITY_KIND_BEAM:
        return modeldesc::Beam::StickModel();
    case ABILITY_KIND_PARASOL:
        return modeldesc::Parasol::ParasolModel();
    case ABILITY_KIND_SPEAR:
        return modeldesc::Spear::SpearModel();
    case ABILITY_KIND_HAMMER:
        return modeldesc::Hammer::HammerModel();
    }
    static gobj::GearModelDesc desc;
    return desc;
}

}
}
}
}
