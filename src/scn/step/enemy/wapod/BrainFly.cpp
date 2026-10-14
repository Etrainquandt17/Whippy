#include "scn/step/enemy/wapod/BrainFly.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/wapod/Custom.h"
#include "scn/step/enemy/wapod/StateAppear.h"
#include "scn/step/enemy/wapod/StateRise.h"
#include "scn/step/enemy/wapod/StateStay.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

BrainFly::BrainFly(Enemy& enemy) : BrainBase(enemy) {}

bool BrainFly::onStart() {
    obj().stateChanger().setNextState<StateAppear, Enemy*>(&obj());
    return true;
}

bool BrainFly::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    u32 variation = custom.wapodpodVariation();
    if (variation == 0xad) {
        obj().stateChanger().setNextState<StateRise, Enemy*>(&obj());
    } else if (variation == 0xae) {
        obj().stateChanger().setNextState<StateStay, Enemy*>(&obj());
    }
    return true;
}

}}}}  // namespace scn::step::enemy::wapod
