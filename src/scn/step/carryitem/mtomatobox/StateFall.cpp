#include "scn/step/carryitem/mtomatobox/StateFall.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/mtomatobox/StateUse.h"

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem, 0xF9) {
    obj().mapColl().setValid(true);
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
}

void StateFall::procAnim() {
    mFallAlgorithm.procAnim();
}

void StateFall::procMove() {
    mFallAlgorithm.procMove();
}

void StateFall::procFixPos() {
    if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*>(objPtr());
    } else {
        mFallAlgorithm.procFixPos();
    }
}

void StateFall::procObjCollReact() {
    mFallAlgorithm.procObjCollReact();
}

}}}}  // namespace scn::step::carryitem::mtomatobox
