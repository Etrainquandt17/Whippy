#include "scn/step/enemy/sheld/BrainChase.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/StateChase.h"
#include "scn/step/enemy/sheld/StateEscape.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

BrainChase::BrainChase(Enemy& enemy) : BrainBase(enemy) {}

bool BrainChase::onLanding() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).isEscape()) {
        obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    }
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).resetNuru();
    return true;
}

}}}}  // namespace scn::step::enemy::sheld
