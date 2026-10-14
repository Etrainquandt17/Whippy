#include "scn/step/enemy/bulby/BrainAttack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/bulby/Custom.h"
#include "scn/step/enemy/bulby/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

BrainAttack::BrainAttack(Enemy& enemy) : BrainBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setIsBuried(true);
}

bool BrainAttack::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainAttack::onRecover() {
    return onStart();
}

}}}}  // namespace scn::step::enemy::bulby
