#ifndef SCN_STEP_ITEM_STATE_STATEBOUND_H
#define SCN_STEP_ITEM_STATE_STATEBOUND_H

#include "scn/step/item/CliffEdgeBoundCtrl.h"
#include "scn/step/item/StateBase.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateBound : public StateBase {
public:
    StateBound(Item* item);
    virtual ~StateBound();

    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    CliffEdgeBoundCtrl mCliffEdgeBoundCtrl;
};

}}}}  // namespace scn::step::item::state

#endif
