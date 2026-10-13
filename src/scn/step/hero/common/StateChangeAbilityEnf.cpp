#include "scn/step/hero/common/StateChangeAbilityEnf.h"
#include "gobj/Move.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Water.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateChangeAbilityEnf::StateChangeAbilityEnf(Hero* hero, AbilityKind kind)
    : StateBase(hero)
    , mKind(kind) {
    obj().move().resetVelocity();
    obj().invincible().setPermNoFlash();
    obj().setCanReactGimmick(false);
    obj().setCanCatchItem(false);
    obj().water().setForbidChangeState(true);
}

StateChangeAbilityEnf::~StateChangeAbilityEnf() {
    obj().setCanReactGimmick(true);
    obj().setCanCatchItem(true);
    obj().water().setForbidChangeState(false);
}

void StateChangeAbilityEnf::procAnim() {
    obj().changeAbilityEnf(mKind);
}

void StateChangeAbilityEnf::procMove() {}

void StateChangeAbilityEnf::procFixPos() {}

}}}}  // namespace scn::step::hero::common
