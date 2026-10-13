#include "scn/step/enemy/waddledoo/StateAttack.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

StateAttack::StateAttack(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(7);
}

void StateAttack::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateAttack::procFixPos() {
    Utility::HitFloorCheck(obj());
}

}}}}  // namespace scn::step::enemy::waddledoo
