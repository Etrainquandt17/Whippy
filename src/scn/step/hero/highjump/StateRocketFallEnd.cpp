#include "scn/step/hero/highjump/StateRocketFallEnd.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/HighjumpParam.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

StateRocketFallEnd::StateRocketFallEnd(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().model().script().start(0xFC);
    obj().invincible().setPerm();
}

StateRocketFallEnd::~StateRocketFallEnd() {
    const HighjumpParam& param = obj().param().highjump();
    obj().abilityManager().setActionInterval(param._9C);
}

void StateRocketFallEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        const HighjumpParam& param = obj().param().highjump();
        obj().invincible().set(param._A0);
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateRocketFallEnd::procMove() {
    const HighjumpParam& param = obj().param().highjump();
    obj().move().setSpeedV(param._A4 * obj().move().velocity().y);
    if (Utility::IsPressHDirKey(obj())) {
        Utility::UpdateMoveTarget(obj());
        obj().move().airAccelFall(obj().target().isRightDir(), param._A8, gobj::MoveParamFall::Zero());
    } else {
        obj().move().airDecelFall(param._B4, gobj::MoveParamFall::Zero());
    }
}

void StateRocketFallEnd::procFixPos() {
}

}
}
}
}
