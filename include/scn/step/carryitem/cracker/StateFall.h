#ifndef SCN_STEP_CARRYITEM_CRACKER_STATEFALL_H
#define SCN_STEP_CARRYITEM_CRACKER_STATEFALL_H

#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

class StateFall : public StateBase {
public:
    StateFall(CarryItem* carryItem);
    virtual ~StateFall();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void explode();
    void reqShake();

private:
    FallAlgorithm mFallAlgorithm;
    f32 mFlashAngle;
    bool mIsExploded;
    u32 mExplodeFrame;
    u32 mShakeFrame;
};

}}}}  // namespace scn::step::carryitem::cracker

#endif
