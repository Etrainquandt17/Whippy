#include "scn/step/boss/lowper/StateFreezeFallAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

StateFreezeFallAttack::StateFreezeFallAttack(Boss* boss, u32 frame)
    : StateBase(boss), mFrame(frame), mCount(0), mStartPos(boss->location().pos()), mGoalPos() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    Utility::ControlHateOnAction(obj());
    mGoalPos = mStartPos;
    mGoalPos.y = 0.5f + obj().basePos().y;
    obj().model().reqScript(0x1F);
    obj().model().rotCtrl().setRotHTarget(0.0f);
    obj().guard().setType(static_cast<GuardType>(4));
}

StateFreezeFallAttack::~StateFreezeFallAttack() {
    obj().objColl().clearAttack(1);
}

void StateFreezeFallAttack::procAnim() {
    if (mCount < mFrame) {
        mCount++;
        if (mCount == mFrame) {
            obj().objColl().clearAttack(1);
            obj().model().reqScript(0x22);
        }
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateFreezeFallAttack::procMove() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 c = 1.0f - Math::CosDegF(90.0f * t);
    f32 rate = c * (c * c);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    custom.waftMoveCtrl().setMoveIntpRate(0.5f);
    custom.waftMoveCtrl().setWaveWidth(0.0f);
    custom.waftMoveCtrl().setCenter(pos);
}

void StateFreezeFallAttack::procFixPos() {}

}}}}  // namespace scn::step::boss::lowper
