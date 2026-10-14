#include "scn/step/enemy/lanzer/BrainWalkAround.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/lanzer/Custom.h"
#include "scn/step/enemy/lanzer/StateWalkAround.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onStart() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.resetTurnFlag();
    obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
    return true;
}

bool BrainWalkAround::onLanding() {
    return onStart();
}

bool BrainWalkAround::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.resetTurnFlag();
    return false;
}

}}}}  // namespace scn::step::enemy::lanzer
