#ifndef SCN_STEP_CARRYITEM_MTOMATOBOX_STATEFALL_H
#define SCN_STEP_CARRYITEM_MTOMATOBOX_STATEFALL_H

#include "scn/step/carryitem/FallAlgorithm.h"
#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

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
};

}}}}  // namespace scn::step::carryitem::mtomatobox

#endif
