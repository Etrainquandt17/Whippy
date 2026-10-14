#include "scn/step/enemy/searches/StateFly.h"

#include "gobj/FootState.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/searches/Custom.h"
#include "scn/step/enemy/searches/StateAttack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace searches {

StateFly::StateFly(Enemy* enemy) : StateBase(enemy) {
    obj().footState().setAir();
    obj().model().reqScript(4);
}

void StateFly::procAnim() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isPlayerInArea()) {
        obj().stateChanger().setNextState<StateAttack, Enemy*>(objPtr());
    }
}

}}}}  // namespace scn::step::enemy::searches
