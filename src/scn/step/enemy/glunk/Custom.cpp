#include "scn/step/enemy/glunk/Custom.h"

#include "app/Random.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/glunk/StateDamageNoSmash.h"
#include "snd/SERequestor.h"

using app::Random;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

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
        Matrix34 mtx;
        setRotate(0.0f);
        mRotate = mRotateTarget;
        mtx = rotateForce(mRotate);
        obj().model().model().setRotateMtx(mtx);
        obj().model().model().updateWorldMtx();
    } else {
        s32 smashType = obj().damageInfo().smashType();
        if (smashType < 6 || smashType > 9) {
            Vector2 pos = obj().location().pos().getXY();
            Vector2 toCenter = obj().location().toCenter().getXY();
            toCenter.rotate(0.017453292f * -mRotate);
            Vector2 center = pos + toCenter;
            Vector2 diff = obj().damageInfo().attackPos() - center;
            f32 angle = 57.29578f * toCenter.signedAngle(diff);
            if (!mIsDamaged) {
                if (angle <= 0.0f) {
                    mRotateTarget -= 10.0f + Random::RandF(-5.0f, 5.0f);
                } else {
                    mRotateTarget += 10.0f + Random::RandF(-5.0f, 5.0f);
                }
                mIsDamaged = true;
            }
        }
    }
    return false;
}

void Custom::onCaptured() {
    Matrix34 mtx;
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
    Vector2 center = obj().location().centerPos().getXY();
    Vector2 left;
    Vector2 right;
    left = Vector2(-0.1f, -1.0f);
    right = Vector2(0.1f, -1.0f);
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

Matrix34 Custom::rotateForce(f32 rotate) {
    Matrix34 up = Matrix34::CreateTrans(Vector3(0.0f, 0.5f, 0.0f));
    Matrix34 down = Matrix34::CreateTrans(Vector3(0.0f, -0.5f, 0.0f));
    Matrix34 rot = Matrix34::CreateRotAxisDeg(Vector3(0.0f, 0.0f, -1.0f), rotate);
    Matrix34 mtx = up * rot * down;
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

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

}}}}  // namespace scn::step::enemy::glunk
