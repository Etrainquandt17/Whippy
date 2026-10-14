#include "scn/step/carryitem/invisiblestone/StateFall.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/invisiblestone/StateUse.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace carryitem {
namespace invisiblestone {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem) {
    obj().mapColl().setValid(true);
    obj().model().reqScript(0);
    obj().effect().release();
    if (obj().useCount() < obj().param().invisibleStone()._0) {
        obj().effect().requestN(static_cast<effect::Kind>(0x34B), 1);
    } else {
        obj().effect().requestN(static_cast<effect::Kind>(0x34D), 1);
    }
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

}}}}  // namespace scn::step::carryitem::invisiblestone
