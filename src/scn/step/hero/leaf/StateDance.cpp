#include "scn/step/hero/leaf/StateDance.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "gobj/Target.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Knockback.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/LeafParam.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

namespace {

inline const LeafParamDance& param(Hero& hero) {
    return hero.param().leaf()._28;
}

}

bool StateDance::TryToChangeState(Hero* hero) {
    if (hero->footState().isGround() && hero->stateChecker().isRun() && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateDance, Hero*>(hero);
        return true;
    }
    return false;
}

StateDance::StateDance(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsEnd(false) {
    obj().mapColl().setThroughOneSpace(true);
    obj().move().resetVelocity();
    obj().invincible().setPerm();
    obj().knockback().setIsValid(false);
    obj().model().script().start(0x9E);
}

StateDance::~StateDance() {
    obj().mapColl().setThroughOneSpace(false);
    if (!mIsEnd) {
        obj().effect()._58.releaseAndVanish();
    }
}

void StateDance::procAnim() {
    mFrame++;
    if (mFrame == param(obj())._0) {
        obj().move().setSpeedH(obj().target().getSign() * param(obj())._4);
    }
    if (obj().model().isAllEnd()) {
        mIsEnd = true;
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateDance::procMove() {
    if (mFrame < param(obj())._8) {
        if (obj().footState().isGround()) {
            obj().move().groundDecel(param(obj())._C);
        } else {
            obj().move().airDecelFall(param(obj())._C, param(obj())._10);
        }
    } else {
        obj().move().airDecelFall(obj().param().common()._74, param(obj())._1C);
    }
}

void StateDance::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
