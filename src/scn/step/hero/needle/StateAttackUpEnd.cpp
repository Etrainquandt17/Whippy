#include "scn/step/hero/needle/StateAttackUpEnd.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/needle/StateAttack.h"
#include "scn/step/hero/needle/StateAttackUp.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

StateAttackUpEnd::StateAttackUpEnd(Hero* hero)
    : StateBase(hero)
    , _8(0) {
    obj().model().script().start(0xBB);
}

StateAttackUpEnd::~StateAttackUpEnd() {
}

void StateAttackUpEnd::procAnim() {
    if (StateAttackUp::TryToChangeState(objPtr()) || StateAttack::TryToChangeState(objPtr())) {
        return;
    }
    if (obj().model().anim().frame() >= 6.0f) {
        Utility::ChangeStateWaitOrFall(obj());
    }
}

void StateAttackUpEnd::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttackUpEnd::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::needle
