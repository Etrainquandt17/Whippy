#ifndef SCN_STEP_ITEM_STATE_STATELOWPERGATHER_H
#define SCN_STEP_ITEM_STATE_STATELOWPERGATHER_H

#include "hel/math/Vector3.h"
#include "scn/step/item/IState.h"

namespace scn {
namespace step {
namespace item {

class Item;

namespace state {

// TODO: members and the other functions.
class StateLowperGather : public IState {
public:
    StateLowperGather(Item* item, const hel::math::Vector3& pos);
    virtual ~StateLowperGather();
};

}}}}  // namespace scn::step::item::state

#endif
