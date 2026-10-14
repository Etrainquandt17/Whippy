#ifndef SCN_STEP_CARRYITEM_COMMON_STATEWAITREPUT_H
#define SCN_STEP_CARRYITEM_COMMON_STATEWAITREPUT_H

#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace common {

class StateWaitReput : public StateBase {
public:
    StateWaitReput(CarryItem* carryItem);
    virtual ~StateWaitReput();
    virtual void procAnim();

private:
    u32 mFrame;
};

}}}}  // namespace scn::step::carryitem::common

#endif
