#include "scn/step/enemy/knucklejoe/BrainWalkStepBack.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/knucklejoe/Custom.h"
#include "scn/step/enemy/knucklejoe/StateWalkStepBack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace knucklejoe {

BrainWalkStepBack::BrainWalkStepBack(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalkStepBack::onStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setHitWall(false);
    obj().stateChanger().setNextState<StateWalkStepBack, Enemy*>(&obj());
    return true;
}

bool BrainWalkStepBack::onLanding() {
    return onStart();
}

void BrainWalkStepBack::update() {
    Utility::ChkNururiTurn(obj());
}

}}}}  // namespace scn::step::enemy::knucklejoe
