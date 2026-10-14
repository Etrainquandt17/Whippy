#include "scn/step/enemy/gemra/BrainWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/gemra/Custom.h"
#include "scn/step/enemy/gemra/StateFly.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWait::onRecover() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).resetPos();
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    obj().stateChanger().setNextState<StateFly, Enemy*>(&obj());
    return true;
}

void BrainWait::update() {}

}}}}  // namespace scn::step::enemy::gemra
