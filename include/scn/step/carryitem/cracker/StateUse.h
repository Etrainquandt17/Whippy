#ifndef SCN_STEP_CARRYITEM_CRACKER_STATEUSE_H
#define SCN_STEP_CARRYITEM_CRACKER_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

// TODO: the source of this state is not written; the members are named after their offsets.
class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem);
    virtual ~StateUse();

    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

    void updateRotMtx();
    void setAttack();
    void clearAttack();

private:
    UseAlgorithm mUseAlgorithm;
    u32 _34;
    f32 _38;
    bool _3C;
    bool _3D;
    u32 _40;
    u32 _44;
};

}}}}  // namespace scn::step::carryitem::cracker

#endif
