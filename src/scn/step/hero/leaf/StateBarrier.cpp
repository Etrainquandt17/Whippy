#include "scn/step/hero/leaf/StateBarrier.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/leaf/StateSpread.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

namespace {

inline const LeafParamBarrier& param(Hero& hero) {
    return hero.param().leaf()._10;
}

}

bool StateBarrier::TryToChangeState(Hero* hero) {
    u32 frame = hero->commandManager().getHoldFrame(static_cast<ButtonMask>(0x20));
    if (hero->footState().isGround() && frame > 5) {
        hero->stateChanger().setNextState<StateBarrier, Hero*>(hero);
        return true;
    }
    return false;
}

StateBarrier::StateBarrier(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsEnd(false) {
    obj().model().script().start(0x9C);
    obj().move().resetSpeedV();
    obj().knockback().setIsValid(false);
}

StateBarrier::~StateBarrier() {
    if (!mIsEnd) {
        obj().effect()._58.releaseAndVanish();
    }
}

void StateBarrier::procAnim() {
    mFrame++;
    if (obj().hid().isHold(0x20)) {
        return;
    }
    if (mFrame >= param(obj())._10) {
        mIsEnd = true;
        obj().stateChanger().setNextState<StateSpread, Hero*>(objPtr());
    } else {
        mIsEnd = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateBarrier::procMove() {
    if (mFrame >= param(obj())._14) {
        if (obj().footState().isGround() && obj().hid().isTrigger(0x10)) {
            obj().footState().setAir();
            obj().move().setSpeedV(param(obj())._C);
        }
        Utility::MoveFromKeyState(obj(), param(obj())._0, obj().param().common()._74, obj().param().common()._90);
    }
}

void StateBarrier::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
