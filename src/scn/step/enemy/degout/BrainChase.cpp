#include "scn/step/enemy/degout/BrainChase.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/degout/Custom.h"
#include "scn/step/enemy/degout/StateChase.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace degout {

BrainChase::BrainChase(Enemy& enemy) : BrainBase(enemy) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setChaseFlag(true);
}

bool BrainChase::onStart() {
    obj().stateChanger().setNextState<common::StateFly, Enemy*>(&obj());
    return true;
}

bool BrainChase::onRecover() {
    obj().stateChanger().setNextState<StateChase, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::degout
