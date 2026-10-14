#include "scn/step/boss/galactaknight/StateSpinAttack.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateSpinAttack::StateSpinAttack(Boss* boss, f32 distance, u32 frame)
    : StateBase(boss), mFrame(frame), mCount(0), mStartPos(boss->location().pos()), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = distance * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    Utility::ControlHateOnAction(obj());
    obj().guard().setType(static_cast<GuardType>(1));
    obj().model().reqScript(0x1A);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    custom.captureCtrl().setCaptureKind(CaptureCtrl::CAPTURE_KIND_0);
}

StateSpinAttack::~StateSpinAttack() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().clearCapture();
    obj().soundSE().loop().stop();
}

void StateSpinAttack::procAnim() {
    if (obj().scriptTrigger().get(2)) {
        generateStar();
    }
    if (obj().scriptTrigger().get(4)) {
        DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().reqStateFinish();
    }
    if (mCount < mFrame) {
        mCount++;
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateSpinAttack::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StateSpinAttack::procFixPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 pos = obj().location().pos();
    pos.y += obj().param().galactaknight()._C0;
    custom.captureCtrl().setConstraintPos(pos);
}

void StateSpinAttack::procObjCollReact() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().checkCapture();
}

void StateSpinAttack::generateStar() {
    const Param& param = obj().param().galactaknight();
    Vector2 pos = param._C;
    Vector2 speed = param._24;
    pos.x *= obj().target().getSign();
    speed.x *= obj().target().getSign();
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    pos.x *= -1.0f;
    speed.x *= -1.0f;
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
}

}}}}  // namespace scn::step::boss::galactaknight
