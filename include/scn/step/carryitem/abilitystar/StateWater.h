#ifndef SCN_STEP_CARRYITEM_ABILITYSTAR_STATEWATER_H
#define SCN_STEP_CARRYITEM_ABILITYSTAR_STATEWATER_H

#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

class StateWater : public StateBase {
public:
    StateWater(CarryItem* carryItem);
    StateWater(CarryItem* carryItem, f32 rot);
    virtual ~StateWater();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    void construct();

private:
    f32 mRot;
    f32 mRotSign;
    bool _10;
    u32 _14;
    f32 mFlashAngle;
};

}}}}  // namespace scn::step::carryitem::abilitystar

#endif
