#include "scn/step/hero/common/StateFaint.h"
#include "gobj/FootState.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateWakeUp.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateFaint::StateFaint(Hero* hero, u32 frame, bool isPauseDisable)
    : StateBase(hero)
    , mFrame(frame)
    , mIsPauseDisable(isPauseDisable) {
    obj().footState().setGround();
    obj().model().script().start(0x2E);
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().incPauseDisableCount();
    }
}

StateFaint::~StateFaint() {
    if (mIsPauseDisable && obj().isMainPlayer()) {
        obj().comp().heroManager().decPauseDisableCount();
    }
}

void StateFaint::procAnim() {
    if (obj().footState().isGround()) {
        if (mFrame != 0) {
            mFrame--;
        } else {
            obj().stateChanger().setNextState<StateWakeUp, Hero*, bool>(objPtr(), mIsPauseDisable);
        }
    }
}

void StateFaint::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateFaint::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
