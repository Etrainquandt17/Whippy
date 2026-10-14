#include "scn/step/boss/doubter/StateTornadoStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateTornadoStart::StateTornadoStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().guard().setType(static_cast<GuardType>(2));
    obj().model().reqScript(11);
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
}

StateTornadoStart::~StateTornadoStart() {}

void StateTornadoStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateTornadoStart::procMove() {
    const Param& param = obj().param().doubter();
    obj().move().groundDecel(param._10);
}

void StateTornadoStart::procFixPos() {}

}}}}  // namespace scn::step::boss::doubter
