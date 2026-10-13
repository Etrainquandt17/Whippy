#include "scn/step/boss/landia/WindCtrl.h"

#include "gobj/Target.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/AreaOperation.h"

namespace scn {
namespace step {
namespace boss {
namespace landia {

namespace {

const f32 T_AREA_RATE[] = { 1.6f, 1.7f, 1.5f, 1.3f, 1.2f, 1.1f, 1.0f };

}

WindCtrl::WindCtrl(Boss& boss) : mBoss(boss), mAreaIds(), mSpeed(0.0f), mAccel(0.0f), mSpeedMax(0.0f) {
    clear();
}

WindCtrl::~WindCtrl() {
    mBoss.comp().areaOperation().clearAllAdditionalVelocity();
}

void WindCtrl::update() {
    mSpeed += mAccel;
    mSpeed = mSpeedMax > 0.0f ? hel::math::Math::Min(mSpeed, mSpeedMax) : hel::math::Math::Max(mSpeed, mSpeedMax);
    for (u32 i = 0; i < 7; i++) {
        hel::math::Vector2 velocity(mSpeed * T_AREA_RATE[i], 0.0f);
        mBoss.comp().areaOperation().setAdditionalVelocity(mAreaIds[i], velocity);
    }
}

void WindCtrl::set(f32 speed, f32 accel, f32 speedMax) {
    mSpeed = speed;
    mAccel = accel;
    mSpeedMax = speedMax;
    mBoss.comp().areaOperation().clearAllAdditionalVelocity();
    hel::math::Vector2 pos = mBoss.location().pos().getXY();
    pos.x -= 3.5f * mBoss.target().getSign();
    for (u32 i = 0; i < 7; i++) {
        hel::geo::Rect rect;
        if (mBoss.target().isRightDir()) {
            rect.set(8.0f, -8.0f, -3.6f, 0.0f);
        } else {
            rect.set(8.0f, -8.0f, 0.0f, 3.6f);
        }
        rect.trans(pos.x, pos.y);
        mAreaIds[i] = mBoss.comp().areaOperation().createAdditionalVelocity(rect);
        pos.x += 3.5f * mBoss.target().getSign();
    }
}

void WindCtrl::clear() {
    set(0.0f, 0.0f, 0.0f);
}

}
}
}
}
