#include "scn/step/hero/bomb/StatePutOnEnemy.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/BombParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/RunChecker.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SubAnimControl.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/bomb/GearBombController.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

StatePutOnEnemy::StatePutOnEnemy(Hero* hero, GearBombController& controller)
    : StateBase(hero)
    , mController(controller)
    , mFrame(0) {
    obj().model().setFixDir(true);
    const BombParam& param = obj().param().bomb();
    if (obj().footState().isAir()) {
        if (obj().move().velocity().y >= 0.0f) {
            obj().move().setSpeedV(param._4);
        } else {
            obj().move().setSpeedV(param._8);
        }
    }
    obj().model().subAnimControl().setLiftUpRHand(false);
    obj().model().script().start(0x111);
}

StatePutOnEnemy::~StatePutOnEnemy() {
    if (mController.isHave()) {
        put();
    }
    const BombParam& param = obj().param().bomb();
    obj().abilityManager().setActionInterval(param._1C);
}

void StatePutOnEnemy::procAnim() {
    if (obj().runChecker().isGroundContinue()) {
        obj().runChecker().setGroundContinue();
    }
    if (obj().model().scriptTrigger().get(0)) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StatePutOnEnemy::procMove() {
    if (obj().runChecker().isGroundContinue()) {
        Utility::MoveDefault(obj());
    } else {
        Utility::MoveDefaultAction(obj());
    }
}

void StatePutOnEnemy::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

bool StatePutOnEnemy::procObjCollReact() {
    return false;
}

void StatePutOnEnemy::put() {
    mController.putBomb();
}

}
}
}
}
