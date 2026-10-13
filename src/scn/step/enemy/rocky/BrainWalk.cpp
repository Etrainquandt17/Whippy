#include "scn/step/enemy/rocky/BrainWalk.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/rocky/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

BrainWalk::BrainWalk(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWalk::onStart() {
    obj().stateChanger().setNextState<common::StateFall, Enemy*>(&obj());
    return true;
}

bool BrainWalk::onRecover() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).setFallSpeedUp(false);
    return onStart();
}

}}}}  // namespace scn::step::enemy::rocky
