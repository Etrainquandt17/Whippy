#include "scn/step/enemy/clayn/Custom.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Model.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/effect/Kind.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/clayn/ParamData.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mRotate(0.0f), mRotateTarget(0.0f), mHideWaitCount(0), mWaitCount(0), mIsDamaged(false) {
    const ParamData& param = obj().param().clayn();
    if (obj().dirType() != static_cast<map::BinEnemyDirType>(0)) {
        mRotateTarget = normalizeAngle(Utility::GetRotByDirType(obj()) + 180.0f);
    } else {
        mRotateTarget = 0.0f;
    }
    mRotate = mRotateTarget;
    switch (obj().level()) {
    case 0:
        mHideWaitCount = param.mHideWaitCount[0];
        mWaitCount = param.mWaitCount[0];
        break;
    case 1:
        mHideWaitCount = param.mHideWaitCount[1];
        mWaitCount = param.mWaitCount[1];
        break;
    default:
        mHideWaitCount = param.mHideWaitCount[2];
        mWaitCount = param.mWaitCount[2];
        break;
    }
    setPos();
}

bool Custom::onInit() {
    rotateForce(mRotate);
    return false;
}

bool Custom::onInWater() {
    obj().soundSE().start(0x2F6);
    return false;
}

bool Custom::onOutWater() {
    return onInWater();
}

void Custom::onProcFixPos() {
    mRotate += (mRotateTarget - mRotate) * 0.1f;
    rotateForce(mRotate);
}

bool Custom::onHitPointIsZero() {
    if (obj().damageInfo().attackType() == 0x12) {
        return false;
    }
    if (obj().damageInfo().element() == 3) {
        hel::math::Matrix34 mtx;
        setRotate(0.0f);
        mRotate = mRotateTarget;
        mtx = rotateForce(mRotate);
        obj().model().model().setRotateMtx(mtx);
        obj().model().model().updateWorldMtx();
    } else {
        s32 smashType = obj().damageInfo().smashType();
        if (!(6 <= smashType && smashType <= 9)) {
            hel::math::Vector2 pos = obj().location().pos().getXY();
            hel::math::Vector2 toCenter = obj().location().toCenter().getXY();
            toCenter.rotate(0.017453292f * -mRotate);
            hel::math::Vector2 center = pos + toCenter;
            hel::math::Vector2 diff = obj().damageInfo().attackPos() - center;
            f32 angle = 57.29578f * toCenter.signedAngle(diff);
            if (!mIsDamaged) {
                if (angle <= 0.0f) {
                    mRotateTarget -= 15.0f + app::Random::RandF(-5.0f, 5.0f);
                } else {
                    mRotateTarget += 15.0f + app::Random::RandF(-5.0f, 5.0f);
                }
                mIsDamaged = true;
            }
        }
    }
    return false;
}

void Custom::onCaptured() {
    hel::math::Matrix34 mtx;
    setRotate(0.0f);
    mRotate = mRotateTarget;
    mtx = rotateForce(mRotate);
    obj().model().model().setRotateMtx(mtx);
    obj().model().model().updateWorldMtx();
}

u32 Custom::getHideWaitCount() const {
    return mHideWaitCount;
}

u32 Custom::getWaitCount() const {
    return mWaitCount;
}

void Custom::setRotate(f32 rotate) {
    mRotateTarget = normalizeAngle(rotate);
}

hel::math::Matrix34 Custom::rotateForce(f32 rotate) {
    hel::math::Matrix34 up = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, 0.5f, 0.0f));
    hel::math::Matrix34 down = hel::math::Matrix34::CreateTrans(hel::math::Vector3(0.0f, -0.5f, 0.0f));
    hel::math::Matrix34 rot = hel::math::Matrix34::CreateRotAxisDeg(hel::math::Vector3(0.0f, 0.0f, -1.0f), rotate);
    hel::math::Matrix34 mtx = up * rot * down;
    obj().model().setCustomMtx(mtx);
    return mtx;
}

f32 Custom::normalizeAngle(f32 angle) const {
    while (angle < -180.0f) {
        angle += 360.0f;
    }
    while (angle >= 180.0f) {
        angle -= 360.0f;
    }
    return angle;
}

void Custom::setPos() {
    hel::math::Vector3 pos = obj().location().pos();
    switch (obj().dirType()) {
    case 4:
    case 5:
        pos.y = static_cast<f32>(static_cast<int>(pos.y + 0.5f));
        break;
    case 2:
    case 3:
        pos.x = static_cast<f32>(static_cast<int>(pos.x));
        pos.x += 0.5f;
        break;
    default:
        pos.y = static_cast<f32>(static_cast<int>(pos.y));
        pos.x = static_cast<f32>(static_cast<int>(pos.x));
        break;
    }
    obj().location().setPos(pos);
}

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}
}
}
}
