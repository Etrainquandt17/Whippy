#include "scn/step/weapon/bombbomb/Expand.h"

#include "hel/math/Math.h"

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

Expand::Expand() : mKind(EXPAND_KIND_NORMAL), mAngle(0.0f), mWait(20), mIsValid(false) {}

void Expand::update() {
    if (!mIsValid) {
        return;
    }
    switch (mKind) {
    case EXPAND_KIND_NORMAL:
        updateNormal();
        break;
    case EXPAND_KIND_FAST:
        updateFast();
        break;
    default:
        updateNormal();
        break;
    }
}

hel::math::Vector3 Expand::scale() {
    if (!mIsValid) {
        return hel::math::Vector3::ALL_ONE;
    }
    f32 sin = hel::math::Math::SinDegF(mAngle);
    return hel::math::Vector3::ALL_ONE * (1.0f + sin * (0.1f * sin));
}

void Expand::setNormal() {
    init(EXPAND_KIND_NORMAL);
}

void Expand::setFast() {
    init(EXPAND_KIND_FAST);
}

void Expand::init(ExpandKind kind) {
    mIsValid = true;
    mAngle = 0.0f;
    mKind = kind;
}

void Expand::updateNormal() {
    if (mWait != 0) {
        mWait--;
        return;
    }
    mAngle += 4.0f;
    if (mAngle > 180.0f) {
        mAngle = 0.0f;
        mWait = 20;
    }
}

void Expand::updateFast() {
    mAngle += 15.0f;
    if (mAngle > 180.0f) {
        mAngle -= 180.0f;
    }
}

}}}}  // namespace scn::step::weapon::bombbomb
