#ifndef SCN_STEP_ITEM_STATE_STATEFALL_H
#define SCN_STEP_ITEM_STATE_STATEFALL_H

#include "scn/step/item/CliffEdgeBoundCtrl.h"
#include "scn/step/item/StateBase.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateFall : public StateBase {
public:
    StateFall(Item* item);
    virtual ~StateFall();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    CliffEdgeBoundCtrl mCliffEdgeBoundCtrl;
};

}}}}  // namespace scn::step::item::state

#endif
