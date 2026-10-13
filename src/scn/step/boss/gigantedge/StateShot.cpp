#include "scn/step/boss/gigantedge/StateShot.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/boss/gigantedge/Custom.h"
#include "scn/step/boss/gigantedge/Param.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

StateShot::StateShot(Boss* boss, Config config) : StateBase(boss), mConfig(config) {
    obj().footState().setGround();
    obj().model().reqScript(15);
}

StateShot::~StateShot() {}

void StateShot::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(0)) {
        custom.reqSwordShot(mConfig._0);
    }
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<common::StateWait, Boss*>(objPtr());
    }
}

void StateShot::procMove() {
    const Param& param = obj().param().gigantedge();
    obj().move().groundDecel(param._38);
}

void StateShot::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}
}
}
}
