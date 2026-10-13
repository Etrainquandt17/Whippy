#include "scn/step/enemy/pluid/Custom.h"

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
#include "snd/SERequestor.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mRotate(0.0f), mRotateTarget(0.0f), mIsRandomFall(false) {
    for (int i = 0; i < 3; i++) {
        mJumpNum[i] = app::Random::Rand(3);
    }
    switch (obj().variation()) {
    case 0x74:
    case 0x7b:
        mRotateTarget = 180.0f;
        break;
    default:
        mRotateTarget = 0.0f;
        break;
    }
    mRotate = mRotateTarget;
}

bool Custom::onInit() {
    rotateForce(mRotate);
    return false;
}

void Custom::onProcFixPos() {
    mRotate += (mRotateTarget - mRotate) * 0.1f;
    rotateForce(mRotate);
}

bool Custom::onDamaged() {
    if (180.0f == mRotateTarget) {
        setRotate(0.0f);
    }
    return false;
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
    obj().model().rotCtrl().resetRot();
}

void Custom::setRotate(f32 rotate) {
    mRotateTarget = normalizeAngle(rotate);
}

int Custom::setJumpNum() {
    int num = app::Random::Rand(3);
    while (mJumpNum[0] == mJumpNum[1] && mJumpNum[1] == mJumpNum[2] && mJumpNum[2] == num) {
        num = app::Random::Rand(3);
    }
    mJumpNum[0] = mJumpNum[1];
    mJumpNum[1] = mJumpNum[2];
    mJumpNum[2] = num;
    return num;
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

Custom::~Custom() {}

void Custom::onRandomFall() {
    mIsRandomFall = true;
}

bool Custom::isRandomFall() const {
    return mIsRandomFall;
}

}
}
}
}
