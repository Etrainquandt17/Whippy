#ifndef SCN_STEP_CARRYITEM_COMMON_STATEVACUUMRECEIVE_H
#define SCN_STEP_CARRYITEM_COMMON_STATEVACUUMRECEIVE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/chara/MoveAlgorithmVacuumReceive.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

class StateVacuumReceive : public StateBase {
public:
    StateVacuumReceive(CarryItem* carryItem, u32 time);
    virtual ~StateVacuumReceive();

    virtual void procAnim();
    virtual void procFixPos();

private:
    chara::MoveAlgorithmVacuumReceive mMoveAlgorithm;
    bool mWasAgeless;
    bool mIsRight;
};

}}}}  // namespace scn::step::carryitem::common

#endif
