#ifndef SCN_STEP_CARRYITEM_ABILITYSTAR_STATEUSE_H
#define SCN_STEP_CARRYITEM_ABILITYSTAR_STATEUSE_H

#include "hel/math/Vector3.h"
#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();

    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsRightDir;
    hel::math::Vector3 mOwnerPos;
};

}}}}  // namespace scn::step::carryitem::abilitystar

#endif
