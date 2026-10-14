#ifndef SCN_STEP_CARRYITEM_PRISMSHIELD_STATEFALL_H
#define SCN_STEP_CARRYITEM_PRISMSHIELD_STATEFALL_H

#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

class StateFall : public StateBase {
public:
    StateFall(CarryItem* carryItem);
    virtual ~StateFall();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void reqShake();

private:
    FallAlgorithm mFallAlgorithm;
    f32 mFlashAngle;
    u32 mShakeFrame;
};

}}}}  // namespace scn::step::carryitem::prismshield

#endif
