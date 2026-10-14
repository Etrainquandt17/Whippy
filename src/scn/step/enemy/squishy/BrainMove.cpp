#include "scn/step/enemy/squishy/BrainMove.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/BrainCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/StateFall.h"
#include "scn/step/enemy/squishy/StateMoveOnLand.h"
#include "scn/step/enemy/squishy/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {}

bool BrainMove::onStart() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isInWater(false)) {
        obj().brainCtrl().toValid();
    } else if (obj().variation() == 0x9f) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveOnLand, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    obj().stateChanger().setNextState<StateFall, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::squishy
