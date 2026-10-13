#include "scn/step/hero/highjump/StateRocketFallStart.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/hero/ButtonMask.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/highjump/StateRocketFall.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

bool StateRocketFallStart::tryToChangeState(Hero* hero) {
    u32 frame = hero->commandManager().getHoldFrame(static_cast<ButtonMask>(0x20));
    if (hero->footState().isAir() && hero->hid().isHold(4) && frame != 0 && frame < 0x14) {
        hero->stateChanger().setNextState<StateRocketFallStart, Hero*, bool>(hero, false);
        return true;
    }
    return false;
}

// The link dropped this function, so its conditions are a guess. It is the second user that keeps
// setNextState out of line.
bool StateRocketFallStart::tryToChangeStateFast(Hero* hero) {
    if (hero->footState().isAir() && hero->hid().isHold(4)) {
        hero->stateChanger().setNextState<StateRocketFallStart, Hero*, bool>(hero, true);
        return true;
    }
    return false;
}

StateRocketFallStart::StateRocketFallStart(Hero* hero, bool isFast)
    : StateBase(hero)
    , mFrame(0)
    , mIsFast(isFast) {
    obj().footState().setAir();
    if (mIsFast) {
        obj().model().script().start(0xFA);
    } else {
        obj().model().script().start(0xF9);
    }
    obj().move().resetVelocity();
}

StateRocketFallStart::~StateRocketFallStart() {
}

void StateRocketFallStart::procAnim() {
    mFrame++;
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateRocketFall, Hero*>(objPtr());
    }
}

void StateRocketFallStart::procMove() {
}

void StateRocketFallStart::procFixPos() {
}

}
}
}
}
