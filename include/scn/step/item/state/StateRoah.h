#ifndef SCN_STEP_ITEM_STATE_STATEROAH_H
#define SCN_STEP_ITEM_STATE_STATEROAH_H

#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateRoah : public StateBase {
public:
    StateRoah(Item* item);
    virtual ~StateRoah();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    f32 mStartY;
    f32 mTargetY;
};

}}}}  // namespace scn::step::item::state

#endif
