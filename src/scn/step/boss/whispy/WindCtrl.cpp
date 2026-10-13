#include "scn/step/boss/whispy/WindCtrl.h"

#include "hel/geo/Rect.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/AreaOperation.h"
#include "std/min.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

const f32 T_AREA_RATE[] = { 1.0f, 1.0f, 1.1f, 1.25f, 1.4f, 1.5f, 1.6f };

}

WindCtrl::WindCtrl(Boss& boss) : mBoss(boss), mSpeed(0.0f), mAccel(0.0f), mSpeedMax(0.0f) {
    hel::math::Vector2 pos = mBoss.location().pos().getXY();
    for (u32 i = 0; i < 7; i++) {
        hel::geo::Rect rect(9.0f, -2.0f, -3.0f, 0.0f);
        rect.trans(pos.x, pos.y);
        mAreaIDs[i] = mBoss.comp().areaOperation().createAdditionalVelocity(rect);
        pos.x -= 2.0f;
    }
}

WindCtrl::~WindCtrl() {
    mBoss.comp().areaOperation().clearAllAdditionalVelocity();
}

void WindCtrl::update() {
    mSpeed += mAccel;
    mSpeed = std::min(mSpeedMax, mSpeed);
    for (u32 i = 0; i < 7; i++) {
        hel::math::Vector2 velocity(mSpeed * T_AREA_RATE[i], 0.0f);
        mBoss.comp().areaOperation().setAdditionalVelocity(mAreaIDs[i], velocity);
    }
}

void WindCtrl::set(f32 speed, f32 accel, f32 speedMax) {
    mSpeed = speed;
    mAccel = accel;
    mSpeedMax = speedMax;
}

void WindCtrl::clear() {
    set(0.0f, 0.0f, 0.0f);
}

}}}}  // namespace scn::step::boss::whispy
