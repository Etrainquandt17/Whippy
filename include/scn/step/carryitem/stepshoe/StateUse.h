#ifndef SCN_STEP_CARRYITEM_STEPSHOE_STATEUSE_H
#define SCN_STEP_CARRYITEM_STEPSHOE_STATEUSE_H

#include "scn/step/carryitem/StateBase.h"
#include "scn/step/carryitem/UseAlgorithm.h"
#include "scn/step/carryitem/stepshoe/ScriptKind.h"

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

class StateUse : public StateBase {
public:
    StateUse(CarryItem* carryItem, f32 flashAngle);
    virtual ~StateUse();

    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();

    void setScale();
    void reqEffect();
    void reqScript(ScriptKind kind);

private:
    UseAlgorithm mUseAlgorithm;
    bool _34;
    bool _35;
    f32 mFlashAngle;
};

}}}}  // namespace scn::step::carryitem::stepshoe

#endif
