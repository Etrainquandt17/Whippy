#include "scn/step/enemy/flamer/BrainAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/flamer/Custom.h"
#include "scn/step/enemy/flamer/StateAgony.h"
#include "scn/step/enemy/flamer/StateChase.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    if (!DynamicCastToRef<Custom, ICustom>(obj().custom()).isAttackEnd()) {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateAgony, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::flamer
