#include "scn/step/hero/common/StateWakeUp.h"

#include "gobj/FootState.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateWakeUp::StateWakeUp(Hero* hero, bool isPauseDisable)
    : StateBase(hero)
    , mIsPauseDisable(isPauseDisable) {
    obj().footState().setGround();
    obj().model().script().start(0x2F);
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().incPauseDisableCount();
    }
}

StateWakeUp::~StateWakeUp() {
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().decPauseDisableCount();
    }
}

void StateWakeUp::procAnim() {
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateWakeUp::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateWakeUp::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
