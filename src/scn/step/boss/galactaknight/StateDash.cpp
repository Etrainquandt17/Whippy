#include "scn/step/boss/galactaknight/StateDash.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateDash::StateDash(Boss* boss, f32 speed, f32 distance)
    : StateBase(boss), mSpeed(speed), mDistance(distance), mIsMove(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xA);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
}

StateDash::~StateDash() {}

void StateDash::procAnim() {
    if (obj().scriptTrigger().get(1)) {
        mIsMove = true;
    }
}

void StateDash::procMove() {
    if (mIsMove) {
        Vector3 pos = obj().location().pos();
        pos.x += mSpeed * obj().target().getSign();
        obj().location().setPos(pos);
    }
}

void StateDash::procFixPos() {
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    Vector3 pos = obj().location().pos();
    if ((heroPos.x - pos.x) * obj().target().getSign() < mDistance) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::galactaknight
