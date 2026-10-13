#include "scn/step/boss/Guard.h"

#include "hel/math/Math.h"

namespace scn {
namespace step {
namespace boss {

namespace {

const f32 T_DAMAGE_PASS_RATE_TABLE[] = { 1.0f, 0.7f, 0.5f, 0.4f, 0.3f, 0.2f, 0.0f };

}

Guard::Guard() : mType(GUARD_TYPE_0) {}

void Guard::setType(GuardType type) {
    mType = type;
}

u32 Guard::calcDamage(u32 damage, f32 rate) {
    if (hel::math::Math::EqZero(rate) && mType == GUARD_TYPE_6) {
        return 0;
    }
    u32 passed = damage * T_DAMAGE_PASS_RATE_TABLE[mType];
    f32 rest = damage - passed;
    u32 result = passed + static_cast<u32>(rest * rate);
    if (result == 0) {
        result = 1;
    }
    return result;
}

}}}  // namespace scn::step::boss
