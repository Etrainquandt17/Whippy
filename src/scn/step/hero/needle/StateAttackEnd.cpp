#include "scn/step/hero/needle/StateAttackEnd.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/needle/StateAttack.h"
#include "scn/step/hero/needle/StateAttackUp.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

StateAttackEnd::StateAttackEnd(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0xB9);
}

StateAttackEnd::~StateAttackEnd() {
}

void StateAttackEnd::procAnim() {
    if (StateAttackUp::TryToChangeState(objPtr()) || StateAttack::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().anim().frame() >= 6.0f) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttackEnd::procMove() {
    Utility::MoveDefaultActionNoOnIce(obj());
}

void StateAttackEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::needle
