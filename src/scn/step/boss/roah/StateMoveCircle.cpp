#include "scn/step/boss/roah/StateMoveCircle.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateMoveCircle::StateMoveCircle(Boss* boss, Config config) : StateBase(boss), mBasePos(), mCount(0), mConfig(config) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    mBasePos = obj().location().pos().getXY();
    obj().model().reqScript(0);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().brainCtrl().toValid();
}

StateMoveCircle::~StateMoveCircle() {}

void StateMoveCircle::procAnim() {
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

void StateMoveCircle::procMove() {
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(mConfig._0);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    hel::math::Vector2 pos = mBasePos;
    pos.x += mConfig._8 * hel::math::Math::SinDegF(360.0f * mConfig._4 * rate);
    pos.y += mConfig._C * hel::math::Math::SinDegF(360.0f * rate);
    obj().location().setPos(pos.toVector3());
}

void StateMoveCircle::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
