#ifndef SCN_STEP_CARRYITEM_CANDLE_STATEFALL_H
#define SCN_STEP_CARRYITEM_CANDLE_STATEFALL_H

#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {
namespace candle {

class StateFall : public StateBase {
public:
    StateFall(CarryItem* carryItem);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void mfBreak();

private:
    FallAlgorithm mFallAlgorithm;
    u32 mWaterFrame;
};

}}}}  // namespace scn::step::carryitem::candle

#endif
