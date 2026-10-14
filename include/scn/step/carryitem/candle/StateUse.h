#ifndef SCN_STEP_CARRYITEM_CANDLE_STATEUSE_H
#define SCN_STEP_CARRYITEM_CANDLE_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"

namespace scn {
namespace step {
namespace carryitem {
namespace candle {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

private:
    UseAlgorithm mUseAlgorithm;
};

}}}}  // namespace scn::step::carryitem::candle

#endif
