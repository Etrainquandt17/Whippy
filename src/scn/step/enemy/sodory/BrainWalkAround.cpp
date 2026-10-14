#include "scn/step/enemy/sodory/BrainWalkAround.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "scn/step/enemy/sodory/StateWalkAround.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

BrainWalkAround::BrainWalkAround(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkAround::onStart() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.setDirectionAll();
    obj().stateChanger().setNextState<StateWalkAround, Enemy*>(&obj());
    return true;
}

bool BrainWalkAround::onLanding() {
    return onStart();
}

bool BrainWalkAround::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.resetBasePosX();
    custom.setDirectionAll();
    custom.setFrame();
    return false;
}

}}}}  // namespace scn::step::enemy::sodory
