#include "scn/step/boss/galactaknight/StateGuard.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateGuard::StateGuard(Boss* boss, f32 distance, u32 frame, u32 guardFrame)
    : StateBase(boss), mFrame(frame), mCount(0), mGuardFrame(guardFrame), mStartPos(boss->location().pos()), mGoalPos() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mGoalPos.x = distance * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = custom.landCtrl().getFloorY();
    obj().model().reqScript(0xC);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_GUARD);
    obj().flash().guard().setIsValid(true);
    obj().guard().setType(static_cast<GuardType>(6));
}

StateGuard::~StateGuard() {
    obj().flash().guard().setIsValid(false);
}

void StateGuard::procAnim() {
    if (mCount < mFrame) {
        mCount++;
    }
    if (mGuardFrame != 0) {
        mGuardFrame--;
        if (mGuardFrame == 0) {
            obj().model().reqScript(0xD);
            obj().flash().guard().setIsValid(false);
            obj().guard().setType(static_cast<GuardType>(0));
            DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
        }
    }
    if (mGuardFrame == 0 && obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateGuard::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
    f32 rate = Math::SinDegF(90.0f * t);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StateGuard::procFixPos() {}

void StateGuard::procObjCollReact() {
    if (mGuardFrame != 0 && obj().objColl().bodyColl().hit().isCollide()) {
        obj().soundSE().normal().start(0x396);
        obj().effect().normal().requestP(static_cast<effect::Kind>(0xDD), obj().location().pos());
    }
}

}}}}  // namespace scn::step::boss::galactaknight
