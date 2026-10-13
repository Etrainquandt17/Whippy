#ifndef SCN_STEP_ITEM_STATE_STATEFALLFEATHERY_H
#define SCN_STEP_ITEM_STATE_STATEFALLFEATHERY_H

#include "scn/step/item/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateFallFeathery : public StateBase {
public:
    StateFallFeathery(Item* item);
    virtual ~StateFallFeathery();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallSpeed;
};

}}}}  // namespace scn::step::item::state

#endif
