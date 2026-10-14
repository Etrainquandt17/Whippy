#ifndef SCN_STEP_CARRYITEM_REPAIRPARTS_STATEUSE_H
#define SCN_STEP_CARRYITEM_REPAIRPARTS_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "util/FrameCounter.h"

namespace scn {
namespace step {
namespace carryitem {
namespace repairparts {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsRightDir;
    bool mIsVisible;
    util::FrameCounter mFrameCounter;
};

}}}}  // namespace scn::step::carryitem::repairparts

#endif
