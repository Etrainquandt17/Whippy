#include "scn/step/boss/goliath/StateJumpFarHero.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/GearModel.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/StateLanding.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateJumpFarHero::StateJumpFarHero(Boss* boss, u32 time, f32 distance)
    : StateBase(boss), mTime(time), mFrame(0), mStartPos(boss->location().pos()), mRot(0.0f), mRotSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    f32 sign = Math::SignF32(custom.landCtrl().getCenterX() - heroPos.x);
    mGoalPos.x = custom.landCtrl().getCenterX() + sign * (0.5f * custom.landCtrl().getWidth()) - distance * sign;
    mGoalPos.y = custom.landCtrl().getFloorYWithBump();
    obj().target().setIsRightDir(mGoalPos.x < custom.landCtrl().getCenterX());
    obj().model().reqScript(0x1E);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateJumpFarHero::~StateJumpFarHero() {
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().reset();
}

void StateJumpFarHero::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else {
        obj().stateChanger().setNextState<StateLanding, Boss*>(objPtr());
        return;
    }
    mRot += mRotSpeed;
    if (mRot >= 360.0f) {
        mRot -= 360.0f;
    }
    if (obj().model().anim().currentG3DAnimIndex() == 0xC) {
        mRotSpeed += 4.0f;
        if (mRotSpeed > 30.0f) {
            mRotSpeed = 30.0f;
        }
    }
    NodeAccessor node = obj().model().model().nodes().at(1);
    node.localMtx().setRTMtx(Matrix34::CreateRotXYZDeg(Vector3(mRot, 0.0f, 0.0f)));
}

void StateJumpFarHero::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y += 4.0f * Math::SinDegF(180.0f * t);
    obj().location().setPos(pos);
}

void StateJumpFarHero::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
