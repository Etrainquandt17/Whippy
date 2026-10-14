#include "scn/step/enemy/pluid/BrainRandomStay.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/pluid/Custom.h"
#include "scn/step/enemy/pluid/StateStay.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

BrainRandomStay::BrainRandomStay(Enemy& enemy) : BrainBase(enemy) {}

bool BrainRandomStay::onStart() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).onRandomFall();
    obj().stateChanger().setNextState<StateStay, Enemy*>(&obj());
    return true;
}

}}}}  // namespace scn::step::enemy::pluid
