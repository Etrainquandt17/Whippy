#include "scn/step/hero/highjump/StateJumpEnd.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/HighjumpParam.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/MapCollResult.h"
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

StateJumpEnd::StateJumpEnd(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().model().script().start(0xF8);
    obj().invincible().setPerm();
}

StateJumpEnd::~StateJumpEnd() {
    const HighjumpParam& param = obj().param().highjump();
    obj().abilityManager().setActionInterval(param._60);
}

void StateJumpEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        MapCollResult result = obj().mapColl().result();
        if (result.mIsHitRoof) {
            obj().move().resetSpeedV();
        }
        const HighjumpParam& param = obj().param().highjump();
        obj().invincible().set(param._64);
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateJumpEnd::procMove() {
    const HighjumpParam& param = obj().param().highjump();
    obj().move().setSpeedV(param._68 * obj().move().velocity().y);
    if (Utility::IsPressHDirKey(obj())) {
        Utility::UpdateMoveTarget(obj());
        obj().move().airAccelFall(obj().target().isRightDir(), param._6C, gobj::MoveParamFall::Zero());
    } else {
        obj().move().airDecelFall(param._78, gobj::MoveParamFall::Zero());
    }
}

void StateJumpEnd::procFixPos() {
}

}}}}  // namespace scn::step::hero::highjump
