#include "scn/step/enemy/bouncy/StateLanding.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"

namespace scn {
namespace step {
namespace enemy {
namespace bouncy {

StateLanding::StateLanding(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setGround();
    obj().model().reqScript(2);
}

void StateLanding::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

}}}}  // namespace scn::step::enemy::bouncy
