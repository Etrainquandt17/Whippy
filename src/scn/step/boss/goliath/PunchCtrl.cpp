#include "scn/step/boss/goliath/PunchCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

PunchCtrl::PunchCtrl(Boss& boss)
    : mBoss(boss), mLength(0.0f), mTargetLength(0.0f), mGenerateStarHeight(0.0f), mIsGenerateStarHeightRegistered(false) {}

void PunchCtrl::update() {
    mLength = 0.5f * (mTargetLength - mLength) + mLength;
    NodeAccessor node = mBoss.model().model().nodes().at(4);
    node.localMtx().setRTMtx(Matrix34::CreateTrans(Vector3(mLength, 0.0f, 0.0f)));
}

void PunchCtrl::setLength(f32 length) {
    mTargetLength = 0.8f * (length - 6.0f);
    if (mTargetLength < 0.0f) {
        mTargetLength = 0.0f;
    }
}

void PunchCtrl::resetLength() {
    setLength(6.0f);
}

void PunchCtrl::registGenerateStarHeight(f32 height) {
    mGenerateStarHeight = height;
    mIsGenerateStarHeightRegistered = true;
}

void PunchCtrl::unregistGenerateStarHeight() {
    mIsGenerateStarHeightRegistered = false;
}

Vector2 PunchCtrl::getGenerateStarSpeedV(f32 height) const {
    const Param& param = mBoss.param().goliath();
    f32 speedY = param._98;
    Vector2 speed(-param._94 * mBoss.target().getSign(), speedY);
    if (height > 3.5f) {
        speed.y *= -1.0f;
    }
    if (mIsGenerateStarHeightRegistered) {
        if (Math::AbsF32(mGenerateStarHeight - height) < 0.5f) {
            speed.y *= -0.8f;
        }
    }
    return speed;
}

}}}}  // namespace scn::step::boss::goliath
