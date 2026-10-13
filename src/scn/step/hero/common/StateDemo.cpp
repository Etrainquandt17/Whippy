#include "scn/step/hero/common/StateDemo.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/Component.h"
#include "scn/step/hero/AdditionalMove.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/InfoUtil.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateDemo::StateDemo(Hero* hero, ScriptKind kind, bool isPauseDisable)
    : StateBase(hero)
    , mIsPauseDisable(isPauseDisable) {
    obj().stateChecker().setDemo(true);
    obj().footState().setGround();
    obj().move().resetVelocity();
    obj().model().script().start(kind);
    obj().setCanReactGimmick(false);
    obj().additionalMove().setValid(false);
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().incPauseDisableCount();
    }
}

StateDemo::~StateDemo() {
    obj().stateChecker().setDemo(false);
    obj().setCanReactGimmick(true);
    obj().additionalMove().setValid(true);
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().decPauseDisableCount();
    }
}

void StateDemo::procAnim() {
    if (obj().model().isAllEnd()) {
        InfoUtil::PlayerNumAppearIfNotLonely(obj());
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateDemo::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateDemo::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
    } else {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

}
}
}
}
