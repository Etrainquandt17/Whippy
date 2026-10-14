#include "scn/step/enemy/pluid/Custom.h"

#include "app/Random.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/DamageInfo.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"

using app::Random;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

Custom::Custom(Enemy& enemy) : CustomBase(enemy), mRotate(0.0f), mRotateTarget(0.0f), mIsRandomFall(false) {
    for (int i = 0; i < 3; i++) {
        mJumpNum[i] = Random::Rand(3);
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
        Matrix34 mtx;
        setRotate(0.0f);
        mRotate = mRotateTarget;
        mtx = rotateForce(mRotate);
        obj().model().model().setRotateMtx(mtx);
        obj().model().model().updateWorldMtx();
    }
    return false;
}

void Custom::onCaptured() {
    Matrix34 mtx;
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
    int num = Random::Rand(3);
    while (mJumpNum[0] == mJumpNum[1] && mJumpNum[1] == mJumpNum[2] && mJumpNum[2] == num) {
        num = Random::Rand(3);
    }
    mJumpNum[0] = mJumpNum[1];
    mJumpNum[1] = mJumpNum[2];
    mJumpNum[2] = num;
    return num;
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

Custom::~Custom() {}

void Custom::onRandomFall() {
    mIsRandomFall = true;
}

bool Custom::isRandomFall() const {
    return mIsRandomFall;
}

}}}}  // namespace scn::step::enemy::pluid
