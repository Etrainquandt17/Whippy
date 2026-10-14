#include "scn/step/enemy/flamer/BrainMove.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateMove.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

BrainMove::BrainMove(Enemy& enemy) : BrainBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsMove(true);
}

bool BrainMove::onStart() {
    if (obj().variation() == 0x29) {
        obj().stateChanger().setNextState<StateMoveCCW, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveCWR, Enemy*>(&obj());
    }
    return true;
}

bool BrainMove::onRecover() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsMove(false);
    return false;
}

}}}}  // namespace scn::step::enemy::flamer
