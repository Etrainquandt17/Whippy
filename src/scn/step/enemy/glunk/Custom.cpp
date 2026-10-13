#include "scn/step/enemy/glunk/Custom.h"

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
#include "scn/step/enemy/glunk/StateDamageNoSmash.h"
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mRotate(0.0f), mRotateTarget(0.0f), mLandAngle(0.0f), mCapturedRotate(0.0f), mIsNoLand(false),
      mIsCurrentFall(false), mIsDamaged(false) {
    if (obj().dirType() != static_cast<map::BinEnemyDirType>(0)) {
        mRotateTarget = normalizeAngle(Utility::GetRotByDirType(obj()) + 180.0f);
    } else {
        mRotateTarget = 0.0f;
    }
    mRotate = mRotateTarget;
    mLandAngle = normalizeAngle(Utility::GetRotByDirType(obj()) + 180.0f) * -1.0f;
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
        if (smashType < 6 || smashType > 9) {
            hel::math::Vector2 pos = obj().location().pos().getXY();
            hel::math::Vector2 toCenter = obj().location().toCenter().getXY();
            toCenter.rotate(0.017453292f * -mRotate);
            hel::math::Vector2 center = pos + toCenter;
            hel::math::Vector2 diff = obj().damageInfo().attackPos() - center;
            f32 angle = 57.29578f * toCenter.signedAngle(diff);
            if (!mIsDamaged) {
                if (angle <= 0.0f) {
                    mRotateTarget -= 10.0f + app::Random::RandF(-5.0f, 5.0f);
                } else {
                    mRotateTarget += 10.0f + app::Random::RandF(-5.0f, 5.0f);
                }
                mIsDamaged = true;
            }
        }
    }
    return false;
}

void Custom::onCaptured() {
    hel::math::Matrix34 mtx;
    mCapturedRotate = mRotateTarget;
    setRotate(0.0f);
    mRotate = mRotateTarget;
    mtx = rotateForce(mRotate);
    obj().model().model().setRotateMtx(mtx);
    obj().model().model().updateWorldMtx();
}

bool Custom::onDamaged() {
    if (obj().damageInfo().smashType() == 9) {
        setRotate(mCapturedRotate);
        mRotate = mRotateTarget;
        obj().model().model().setRotateMtx(rotateForce(mRotate));
        obj().model().model().updateWorldMtx();
    }
    obj().stateChanger().setNextState<StateDamageNoSmash, Enemy*>(&obj());
    return true;
}

// TODO: the link dropped this function; the member it returns is a guess.
f32 Custom::rotate() const {
    return mRotateTarget;
}

void Custom::setRotate(f32 rotate) {
    mRotateTarget = normalizeAngle(rotate);
}

bool Custom::isCurrentFall() const {
    return mIsCurrentFall;
}

void Custom::setIsCurrentFall(bool isCurrentFall) {
    mIsCurrentFall = isCurrentFall;
}

bool Custom::checkExistLand() {
    hel::math::Vector2 center = obj().location().centerPos().getXY();
    hel::math::Vector2 left;
    hel::math::Vector2 right;
    left = hel::math::Vector2(-0.1f, -1.0f);
    right = hel::math::Vector2(0.1f, -1.0f);
    left.rotate(0.017453292f * mLandAngle);
    right.rotate(0.017453292f * mLandAngle);
    left += center;
    right += center;
    int leftX = static_cast<int>(left.x);
    int leftY = static_cast<int>(left.y);
    int rightX = static_cast<int>(right.x);
    int rightY = static_cast<int>(right.y);
    if (obj().dirType() != static_cast<map::BinEnemyDirType>(5) && !mIsNoLand) {
        if (!Utility::IsExistLand(obj(), static_cast<f32>(leftX), static_cast<f32>(leftY))
            || !Utility::IsExistLand(obj(), static_cast<f32>(rightX), static_cast<f32>(rightY))) {
            mLandAngle = 0.0f;
            mIsNoLand = true;
            return false;
        }
        return true;
    }
    if (!Utility::IsExistLand(obj(), static_cast<f32>(leftX), static_cast<f32>(leftY))
        && !Utility::IsExistLand(obj(), static_cast<f32>(rightX), static_cast<f32>(rightY))) {
        return false;
    }
    return true;
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

const hel::common::RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<Custom>();
}

}
}
}
}
