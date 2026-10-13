#ifndef SCN_STEP_ITEM_STATE_STATEGATHER_H
#define SCN_STEP_ITEM_STATE_STATEGATHER_H

#include "hel/math/Vector2.h"
#include "scn/step/item/Catcher.h"
#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateGather : public StateBase {
public:
    StateGather(Item* item, Catcher& catcher);

    virtual void procAnim();
    virtual void procMove();

private:
    f32 mFrame;
    hel::math::Vector2 mStartPos;
    Catcher& mCatcher;
};

}}}}  // namespace scn::step::item::state

#endif
