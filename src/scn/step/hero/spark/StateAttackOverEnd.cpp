#include "scn/step/hero/spark/StateAttackOverEnd.h"
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

StateAttackOverEnd::StateAttackOverEnd(Hero* hero)
    : StateBase(hero) {
    obj().abilityManager().customSpark().setAction(true);
    obj().model().script().start(0xCD);
}

StateAttackOverEnd::~StateAttackOverEnd() {
    obj().abilityManager().customSpark().setAction(false);
}

void StateAttackOverEnd::procAnim() {
    if (obj().abilityManager().tryToChangeState()) {
        return;
    }
    if (obj().model().isAllEnd()) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttackOverEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttackOverEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::spark
