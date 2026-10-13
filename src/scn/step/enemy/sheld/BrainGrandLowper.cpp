#include "scn/step/enemy/sheld/BrainGrandLowper.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sheld/Custom.h"
#include "scn/step/enemy/sheld/StateChase.h"
#include "scn/step/enemy/sheld/StateEscape.h"
#include "scn/step/enemy/sheld/StateGrandLowperAppear.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

BrainGrandLowper::BrainGrandLowper(Enemy& enemy) : BrainBase(enemy) {}

bool BrainGrandLowper::onStart() {
    obj().stateChanger().setNextState<StateGrandLowperAppear, Enemy*>(&obj());
    return true;
}

bool BrainGrandLowper::onLanding() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.isEscape()) {
        obj().stateChanger().setNextState<StateEscape, Enemy*>(&obj());
    } else {
        obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    }
    custom.resetNuru();
    return true;
}

}}}}  // namespace scn::step::enemy::sheld
