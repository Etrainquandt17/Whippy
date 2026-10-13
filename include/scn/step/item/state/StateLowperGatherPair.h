#ifndef SCN_STEP_ITEM_STATE_STATELOWPERGATHERPAIR_H
#define SCN_STEP_ITEM_STATE_STATELOWPERGATHERPAIR_H

#include "scn/step/item/IState.h"

namespace scn {
namespace step {
namespace item {

class Item;

namespace state {

// TODO: members and the other functions.
class StateLowperGatherPair : public IState {
public:
    StateLowperGatherPair(Item* item);
    virtual ~StateLowperGatherPair();
};

}}}}  // namespace scn::step::item::state

#endif
