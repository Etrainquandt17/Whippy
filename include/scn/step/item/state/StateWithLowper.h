#ifndef SCN_STEP_ITEM_STATE_STATEWITHLOWPER_H
#define SCN_STEP_ITEM_STATE_STATEWITHLOWPER_H

#include "hel/math/Vector3.h"
#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateWithLowper : public StateBase {
public:
    StateWithLowper(Item* item);
    virtual ~StateWithLowper();

    virtual void procAnim();

private:
    hel::math::Vector3 mBasePos;
    f32 mAngle;
};

}}}}  // namespace scn::step::item::state

#endif
