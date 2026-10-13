#include "scn/step/hero/needle/StateDashEnd.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Script.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/NeedleParam.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

StateDashEnd::StateDashEnd(Hero* hero)
    : StateBase(hero)
    , mIsRight(obj().move().velocity().x > 0.0f) {
    obj().model().script().start(0xBD);
    obj().invincible().setPerm();
}

StateDashEnd::~StateDashEnd() {
    obj().move().resetSpeedH();
}

void StateDashEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateDashEnd::procMove() {
    if (obj().footState().isGround()) {
        obj().move().groundAccel(mIsRight, gobj::MoveParamAccel::Create(0.065f, 0.0f, 0.02f));
    } else {
        const NeedleParam& param = obj().param().needle();
        obj().move().airAccelFall(mIsRight, gobj::MoveParamAccel::Create(0.065f, 0.0f, 0.02f), param._68);
    }
}

void StateDashEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::needle
