#include "scn/step/enemy/carrydee/BrainWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/carrydee/Custom.h"
#include "scn/step/enemy/carrydee/StateWait.h"
#include "scn/step/enemy/common/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isHaveKey()) {
        obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<common::StateWait, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::carrydee
