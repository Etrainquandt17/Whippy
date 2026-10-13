#include "scn/step/hero/sword/StateSwordChopping.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/SwordParam.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateFall.h"
#include "scn/step/hero/common/StateHover.h"
#include "scn/step/hero/common/StateWait.h"
#include "scn/step/hero/sword/StateSwordChoppingHit.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

bool StateSwordChopping::TryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && !hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordChopping, Hero*, bool>(hero, false);
        return true;
    }
    return false;
}

bool StateSwordChopping::RetryToChangeState(Hero* hero) {
    if (hero->footState().isAir() && !hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateSwordChopping, Hero*, bool>(hero, true);
        return true;
    }
    return false;
}

StateSwordChopping::StateSwordChopping(Hero* hero, bool isRetry)
    : StateBase(hero)
    , mFrame(0)
    , mIsRetry(isRetry) {
    obj().footState().setAir();
    obj().model().setFixDir(true);
    obj().model().script().start(0x84);
    if (!mIsRetry) {
        Utility::AirAttackInitSpeedV(obj());
    }
}

StateSwordChopping::~StateSwordChopping() {
}

void StateSwordChopping::procAnim() {
    const SwordParam& param = obj().param().sword();
    mFrame++;
    if (mFrame >= param._18) {
        if (RetryToChangeState(objPtr()) || common::StateHover::TryToChangeState(objPtr())) {
            return;
        }
    }
    if (mFrame == param._1C) {
        obj().stateChanger().setNextState<common::StateFall, Hero*>(objPtr());
    }
}

void StateSwordChopping::procMove() {
    Utility::MoveDefault(obj());
}

void StateSwordChopping::procFixPos() {
    if (common::StateWait::TryToChangeStateWithScript(objPtr(), static_cast<ScriptKind>(3))) {
        return;
    }
}

bool StateSwordChopping::procObjCollReact() {
    if (obj().objColl().objColl().isAttackCollide()) {
        obj().stateChanger().setNextState<StateSwordChoppingHit, Hero*>(objPtr());
        return true;
    }
    return false;
}

}}}}  // namespace scn::step::hero::sword
