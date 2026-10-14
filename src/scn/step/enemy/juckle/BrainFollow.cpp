#include "scn/step/enemy/juckle/BrainFollow.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/juckle/Custom.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

BrainFollow::BrainFollow(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFollow::onStart() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.onFollowFlag();
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainFollow::onRecover() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::juckle
