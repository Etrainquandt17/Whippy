#ifndef SCN_GOALGAME_DESC_GEAR_GEARDESC_H
#define SCN_GOALGAME_DESC_GEAR_GEARDESC_H

#include "gobj/GearAnim.h"
#include "gobj/GearModel.h"
#include "scn/step/hero/AbilityKind.h"
#include "types.h"

namespace scn {
namespace goalgame {
namespace desc {
namespace gear {

class GearDesc {
public:
    static bool isUseGear(step::hero::AbilityKind kind);
    static bool isUseModel(step::hero::AbilityKind kind);
    static const gobj::GearAnimDesc& Anim(step::hero::AbilityKind kind);
    static const gobj::GearModelDesc& Model(step::hero::AbilityKind kind);
};

}
}
}
}

#endif
