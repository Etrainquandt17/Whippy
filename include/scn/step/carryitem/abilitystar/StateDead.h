#ifndef SCN_STEP_CARRYITEM_ABILITYSTAR_STATEDEAD_H
#define SCN_STEP_CARRYITEM_ABILITYSTAR_STATEDEAD_H

#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

class StateDead : public StateBase {
public:
    StateDead(CarryItem* carryItem, bool isLong);
    virtual ~StateDead();

    virtual void procAnim();
    virtual void procMove();

private:
    u32 mFrame;
    bool mIsLong;
};

}}}}  // namespace scn::step::carryitem::abilitystar

#endif
