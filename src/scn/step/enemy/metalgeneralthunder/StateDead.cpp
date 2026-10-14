#include "scn/step/enemy/metalgeneralthunder/StateDead.h"

#include "gobj/FootState.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

StateDead::StateDead(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
}

StateDead::~StateDead() {}

void StateDead::procAnim() {
    obj().deadWithEffect();
}

void StateDead::procMove() {}

void StateDead::procFixPos() {}

}}}}  // namespace scn::step::enemy::metalgeneralthunder
