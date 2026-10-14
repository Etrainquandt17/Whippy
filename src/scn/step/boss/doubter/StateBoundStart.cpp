#include "scn/step/boss/doubter/StateBoundStart.h"

#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/boss/doubter/StateBound.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateBoundStart::StateBoundStart(Boss* boss, const Vector2& speed, u32 count) : StateBase(boss), mSpeed(speed), mCount(count) {
    obj().model().reqScript(7);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateBoundStart::~StateBoundStart() {}

void StateBoundStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateBound, Boss*, Vector2, u32>(objPtr(), mSpeed, mCount);
    }
}

void StateBoundStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateBoundStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
