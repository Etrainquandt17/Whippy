#ifndef SCN_STEP_ITEM_STATE_STATEFIXED_H
#define SCN_STEP_ITEM_STATE_STATEFIXED_H

#include "scn/step/item/StateBase.h"

namespace scn {
namespace step {
namespace item {
namespace state {

class StateFixed : public StateBase {
public:
    StateFixed(Item* item);
    virtual void procMove();
};

}}}}  // namespace scn::step::item::state

#endif
