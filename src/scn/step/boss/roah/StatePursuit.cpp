#include "scn/step/boss/roah/StatePursuit.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace roah {

StatePursuit::StatePursuit(Boss* boss, Config config) : StateBase(boss), mCount(0), mConfig(config) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().brainCtrl().toValid();
    Utility::ControlHateOnAction(obj());
}

StatePursuit::~StatePursuit() {}

void StatePursuit::procAnim() {
    mCount++;
    if (obj().scriptTrigger().get(1)) {
        obj().model().reqScript(7);
    }
    if (obj().scriptTrigger().get(3)) {
        obj().model().reqScript(8);
    }
    if (obj().scriptTrigger().get(5)) {
        obj().model().reqScript(9);
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
    if (mCount == mConfig._0) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StatePursuit::procMove() {
    const Param& param = obj().param().roah();
    f32 heroY = Utility::GetHatedHeroPos(obj()).y;
    if (Math::Abs(heroY - obj().location().pos().y) > param.mPursuitMargin) {
        bool isUp = heroY > obj().location().pos().y;
        Vector3 dir = Vector3::BASIS_Y * (isUp ? 1.0f : -1.0f);
        obj().move().accel(dir, mConfig._4);
    } else {
        obj().move().decel(gobj::MoveParamDecel::Create(mConfig._4._8));
    }
}

void StatePursuit::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
