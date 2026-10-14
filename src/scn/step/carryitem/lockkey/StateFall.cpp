#include "scn/step/carryitem/lockkey/StateFall.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/lockkey/StateUse.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem)
    , mFlash(*carryItem) {
    obj().mapColl().setValid(true);
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
}

void StateFall::procAnim() {
    mFallAlgorithm.procAnim();
    mFlash.update();
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

}}}}  // namespace scn::step::carryitem::lockkey
