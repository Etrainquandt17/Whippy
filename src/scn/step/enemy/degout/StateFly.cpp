#include "scn/step/enemy/degout/StateFly.h"

#include "gobj/FootState.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/degout/ParamData.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy), mFrame(0) {
    obj().footState().setAir();
    obj().model().reqScript(7);
    obj().brainCtrl().toValid();
}

void StateFly::procAnim() {
    mFrame++;
    if (mFrame == obj().param().degout()._3c[6]) {
        obj().model().reqScript(4);
    }
}

}}}}  // namespace scn::step::enemy::degout
