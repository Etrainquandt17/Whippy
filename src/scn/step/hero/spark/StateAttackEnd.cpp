#include "scn/step/hero/spark/StateAttackEnd.h"
#include "gobj/Script.h"
#include "scn/step/hero/AbilityManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/spark/Custom.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

StateAttackEnd::StateAttackEnd(Hero* hero)
    : StateBase(hero) {
    obj().abilityManager().customSpark().setAction(true);
    obj().model().script().start(0xCB);
}

StateAttackEnd::~StateAttackEnd() {
    obj().abilityManager().customSpark().setAction(false);
}

void StateAttackEnd::procAnim() {
    if (obj().abilityManager().tryToChangeState()) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttackEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttackEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
