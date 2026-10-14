#ifndef SCN_STEP_CARRYITEM_PRISMSHIELD_STATEUSE_H
#define SCN_STEP_CARRYITEM_PRISMSHIELD_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();

    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

    bool isUpdateAttack();
    bool isSameDir();
    void chkAnim();
    void setAttack();
    void reqReleaseEffect();

private:
    UseAlgorithm mUseAlgorithm;
    f32 mFlashAngle;
    bool mIsRightDir;
    bool mIsRightDirPrev;
    bool mIsStart;
    bool mIsReleased;
    bool mIsGuard;
    bool mIsGuardPrev;
};

}}}}  // namespace scn::step::carryitem::prismshield

#endif
