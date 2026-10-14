#ifndef SCN_STEP_CARRYITEM_MTOMATOBOX_STATEBOUND_H
#define SCN_STEP_CARRYITEM_MTOMATOBOX_STATEBOUND_H

#include "scn/step/carryitem/BoundAlgorithm.h"
#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

class StateBound : public StateBase {
public:
    StateBound(CarryItem* carryItem);
    virtual ~StateBound();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    bool isChangeWait();
    void crash();
    void flash();

private:
    FallAlgorithm mFallAlgorithm;
    BoundAlgorithm mBoundAlgorithm;
    bool mIsWait;
    bool mIsCrashed;
    u32 mWaitFrame;
    f32 mFlashAngle;
    u32 mBoundCount;
};

}}}}  // namespace scn::step::carryitem::mtomatobox

#endif
