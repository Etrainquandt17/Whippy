#ifndef SCN_STEP_ITEM_STATE_STATELOWPERHIDE_H
#define SCN_STEP_ITEM_STATE_STATELOWPERHIDE_H

#include "scn/step/item/IState.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

}
namespace item {

class Item;

namespace state {

// TODO: members and the other functions.
class StateLowperHide : public IState {
public:
    StateLowperHide(Item* item, boss::Boss& boss);
    virtual ~StateLowperHide();
};

}}}}  // namespace scn::step::item::state

#endif
