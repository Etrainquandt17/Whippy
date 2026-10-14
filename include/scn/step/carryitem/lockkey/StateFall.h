#ifndef SCN_STEP_CARRYITEM_LOCKKEY_STATEFALL_H
#define SCN_STEP_CARRYITEM_LOCKKEY_STATEFALL_H

#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/lockkey/Flash.h"

namespace scn {
namespace step {
namespace carryitem {
namespace lockkey {

class StateFall : public StateBase {
public:
    StateFall(CarryItem* carryItem);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    FallAlgorithm mFallAlgorithm;
    Flash mFlash;
};

}}}}  // namespace scn::step::carryitem::lockkey

#endif
