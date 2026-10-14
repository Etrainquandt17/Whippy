#include "scn/step/enemy/sodory/BrainWait.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/sodory/Custom.h"
#include "scn/step/enemy/sodory/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy) {}

bool BrainWait::onStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).setDirectionAll();
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    return true;
}

bool BrainWait::onLanding() {
    return onStart();
}

bool BrainWait::onRecover() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.setDirectionAll();
    custom.setFrame();
    return false;
}

}}}}  // namespace scn::step::enemy::sodory
