#include "scn/step/boss/doubter/StateTornadoSearch.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateTornadoFall.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateTornadoSearch::StateTornadoSearch(Boss* boss, u32 frame, f32 rate)
    : StateBase(boss), mFrame(frame), mCount(0), mAccel(boss->param().doubter()._B0) {
    obj().footState().setAir();
    mAccel._0 *= rate;
    mAccel._4 *= rate;
    mAccel._8 *= rate;
    obj().move().resetVelocity();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(14);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_3);
}

StateTornadoSearch::~StateTornadoSearch() {}

void StateTornadoSearch::procAnim() {
    mCount++;
    if (mCount >= mFrame) {
        obj().move().resetVelocity();
        obj().stateChanger().setNextState<StateTornadoFall, Boss*>(objPtr());
        return;
    }
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    f32 distance = Math::AbsF32(heroPos.x - obj().location().pos().x);
    if (distance > obj().param().doubter()._AC) {
        Utility::TurnHatedHero(obj());
    }
}

void StateTornadoSearch::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().airAccelFall(obj().target().isRightDir(), mAccel, param._BC);
}

void StateTornadoSearch::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
