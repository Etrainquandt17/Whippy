#ifndef SCN_STEP_ITEM_STATE_STATEABILITYSEATFIXED_H
#define SCN_STEP_ITEM_STATE_STATEABILITYSEATFIXED_H

#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateAbilitySeatFixed : public StateBase {
public:
    StateAbilitySeatFixed(Item* item, f32 rot);
    virtual ~StateAbilitySeatFixed();
    virtual void procAnim();

private:
    f32 mRot;
};

}}}}  // namespace scn::step::item::state

#endif
