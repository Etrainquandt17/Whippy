#include "scn/step/weapon/bombbomb/Flash.h"

#include "hel/math/Math.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/bombbomb/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

Flash::Flash(Weapon& weapon)
    : mObj(weapon)
    , mKind(FLASH_KIND_NORMAL)
    , mAngle(0.0f)
    , mWait(weapon.param().bombBomb()._9C) {}

void Flash::update() {
    switch (mKind) {
    case FLASH_KIND_NORMAL:
        updateNormal();
        break;
    case FLASH_KIND_FAST:
        updateFast();
        break;
    default:
        updateNormal();
        break;
    }
}

void Flash::setFast() {
    mKind = FLASH_KIND_FAST;
    mAngle = 0.0f;
}

void Flash::updateNormal() {
    const Param& param = mObj.param().bombBomb();
    if (mWait != 0) {
        mWait--;
    } else {
        mAngle += param._A4;
        if (mAngle > 90.0f) {
            mAngle = 0.0f;
            mWait = param._A0;
        }
    }
}

void Flash::updateFast() {
    mAngle += mObj.param().bombBomb()._A8;
    if (mAngle > 180.0f) {
        mAngle -= 180.0f;
    }
}

::GXColor Flash::GXColor() {
    const Param& param = mObj.param().bombBomb();
    f32 sin = hel::math::Math::SinDegF(mAngle);
    u8 alpha = sin * param._AC;
    ::GXColor color;
    color.r = param._B0;
    color.g = 0x10;
    color.b = 0;
    color.a = alpha;
    return color;
}

}}}}  // namespace scn::step::weapon::bombbomb
