#ifndef SCN_STEP_ITEM_STATE_STATEAPPROACH_H
#define SCN_STEP_ITEM_STATE_STATEAPPROACH_H

#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateApproach : public StateBase {
public:
    StateApproach(Item* item);
    virtual void procAnim();
    virtual void procMove();

private:
    f32 mRate;
};

}}}}  // namespace scn::step::item::state

#endif
