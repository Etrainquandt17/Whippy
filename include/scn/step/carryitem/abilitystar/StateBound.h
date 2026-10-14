#ifndef SCN_STEP_CARRYITEM_ABILITYSTAR_STATEBOUND_H
#define SCN_STEP_CARRYITEM_ABILITYSTAR_STATEBOUND_H

#include "hel/math/Vector3.h"
#include "scn/step/carryitem/BoundAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {
namespace abilitystar {

// TODO: the source of this state is not written; the members are what its constructor sets.
class StateBound : public StateBase {
public:
    StateBound(CarryItem* carryItem, bool, bool isRightDir);
    virtual ~StateBound();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    BoundAlgorithm mBoundAlgorithm;
    f32 _38;
    f32 _3C;
    u32 _40;
    f32 _44;
    f32 _48;
    f32 _4C;
    f32 _50;
};

}}}}  // namespace scn::step::carryitem::abilitystar

#endif
