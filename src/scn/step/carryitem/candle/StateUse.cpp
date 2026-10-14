#include "scn/step/carryitem/candle/StateUse.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/candle/StateFall.h"
#include "scn/step/carryitem/candle/Utility.h"
#include "scn/step/chara/Effect.h"

namespace scn {
namespace step {
namespace carryitem {
namespace candle {

StateUse::StateUse(CarryItem* carryItem)
    : StateBase(carryItem)
    , mUseAlgorithm(*carryItem) {
    Utility::ChkWater(obj());
    obj().effectBack().release();
    if (obj().useCount() == 0) {
        obj().effectBack().requestN(static_cast<effect::Kind>(0x336), 0);
    }
}

StateUse::~StateUse() {}

void StateUse::procAnim() {
    mUseAlgorithm.procAnim();
}

void StateUse::procMove() {
    mUseAlgorithm.procMove();
}

void StateUse::procConstraint() {
    Utility::ChkWater(obj());
    if (mUseAlgorithm.procConstraint()) {
        obj().stateChanger().setNextState<StateFall, CarryItem*>(objPtr());
    }
}

}}}}  // namespace scn::step::carryitem::candle
