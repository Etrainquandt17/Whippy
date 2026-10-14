#ifndef SCN_STEP_CARRYITEM_LOCKKEY_STATEUSE_H
#define SCN_STEP_CARRYITEM_LOCKKEY_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"
#include "scn/step/carryitem/lockkey/Flash.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

private:
    UseAlgorithm mUseAlgorithm;
    bool mIsHeroUser;
    Flash mFlash;
};

}}}}  // namespace scn::step::carryitem::lockkey

#endif
