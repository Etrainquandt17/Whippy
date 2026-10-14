#include "scn/step/enemy/sheld/BrainDash.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/StateDash.h"
#include "scn/step/enemy/sheld/StateEscape.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

BrainDash::BrainDash(Enemy& enemy) : BrainBase(enemy) {}

bool BrainDash::onLanding() {
    if (DynamicCastToRef<Custom, ICustom>(obj().custom()).isEscape()) {
        obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateDash, Enemy*>(&obj());
    }
    return true;
}

void BrainDash::update() {}

}}}}  // namespace scn::step::enemy::sheld
