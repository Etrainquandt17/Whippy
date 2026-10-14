#ifndef SCN_STEP_CARRYITEM_REPAIRPARTS_STATEREPAIRTHROW_H
#define SCN_STEP_CARRYITEM_REPAIRPARTS_STATEREPAIRTHROW_H

#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace repairparts {

class StateRepairThrow : public StateBase {
public:
    StateRepairThrow(CarryItem* carryItem);
    virtual ~StateRepairThrow();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::carryitem::repairparts

#endif
