#include "scn/step/enemy/flamer/BrainMoveAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateAgony.h"
#include "scn/step/enemy/flamer/StateChase.h"
#include "scn/step/enemy/flamer/StateMove.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

BrainMoveAttack::BrainMoveAttack(Enemy& enemy) : BrainBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsMove(true);
}

bool BrainMoveAttack::onStart() {
    if (obj().variation() == 0x2b) {
        obj().stateChanger().setNextState<StateMoveCCW, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateMoveCWR, Enemy*>(&obj());
    }
    return true;
}

bool BrainMoveAttack::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (!custom.isAttackEnd()) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateAgony, Enemy*>(&obj());
    }
    custom.setIsMove(false);
    return true;
}

}}}}  // namespace scn::step::enemy::flamer
