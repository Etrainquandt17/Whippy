#include "scn/step/boss/dubior/StateDash.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/dubior/Custom.h"
#include "scn/step/boss/dubior/Param.h"
#include "scn/step/boss/dubior/StateDashWallHit.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

StateDash::StateDash(Boss* boss) : StateBase(boss), mIsDash(false) {
    const Param& param = obj().param().dubior();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(6);
    obj().move().setSpeedH(param.mDashBackSpeed * -obj().target().getSign());
    custom.setBodyCollDash();
}

StateDash::~StateDash() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setBodyCollDefault();
}

void StateDash::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsDash = true;
        obj().move().resetVelocity();
        obj().guard().setType(GUARD_TYPE_5);
    }
}

void StateDash::procMove() {
    const Param& param = obj().param().dubior();
    if (mIsDash) {
        Vector3 dir = Vector3::BASIS_X;
        dir.x *= obj().target().getSign();
        obj().move().accel(dir, param.mDashAccel);
    } else {
        obj().move().decel(param.mDashDecel);
    }
}

void StateDash::procFixPos() {
    if (mIsDash) {
        chara::MapCollResult result = obj().mapColl().result();
        if (result._2 || obj().worldCage().isCorrected()) {
            obj().stateChanger().setNextState<StateDashWallHit, Boss*>(objPtr());
        }
    }
}

}}}}  // namespace scn::step::boss::dubior
