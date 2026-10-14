#ifndef SCN_STEP_CARRYITEM_COMMON_STATESPACEJUMP_H
#define SCN_STEP_CARRYITEM_COMMON_STATESPACEJUMP_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

class StateSpaceJump : public StateBase {
public:
    StateSpaceJump(CarryItem* carryItem);
    virtual ~StateSpaceJump();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

private:
    UseAlgorithm mUseAlgorithm;
};

}}}}  // namespace scn::step::carryitem::common

#endif
