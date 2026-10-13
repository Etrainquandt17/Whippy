#include "scn/step/hero/spark/StateAttackUnderEnd.h"
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

StateAttackUnderEnd::StateAttackUnderEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0xCF);
    obj().abilityManager().customSpark().setAction(true);
}

StateAttackUnderEnd::~StateAttackUnderEnd() {
    obj().abilityManager().customSpark().setAction(false);
}

void StateAttackUnderEnd::procAnim() {
    if (obj().abilityManager().tryToChangeState()) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttackUnderEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttackUnderEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
