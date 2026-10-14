#include "scn/step/carryitem/mtomatobox/StateUse.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/mtomatobox/StateBound.h"
#include "scn/step/carryitem/mtomatobox/StateFall.h"

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem) {
    obj().vanishObjGenerator();
}

StateUse::~StateUse() {}

void StateUse::procAnim() {
    mUseAlgorithm.procAnim();
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    if (mUseAlgorithm.procConstraint()) {
        if (obj().getReleaseType() == RELEASE_TYPE_PUT) {
            obj().stateChanger().setNextState<StateFall, CarryItem*>(objPtr());
        } else {
            obj().stateChanger().setNextState<StateBound, CarryItem*>(objPtr());
        }
    }
}

}}}}  // namespace scn::step::carryitem::mtomatobox
