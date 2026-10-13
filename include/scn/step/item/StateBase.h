#ifndef SCN_STEP_ITEM_STATEBASE_H
#define SCN_STEP_ITEM_STATEBASE_H

#include "scn/step/item/IState.h"

namespace scn {
namespace step {
namespace item {

class Item;

// TODO: the three proc functions are IState's, which does not declare them yet.
class StateBase : public IState {
public:
    StateBase(Item* item);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

    Item& obj() const;
    Item& obj();
    Item* objPtr();

private:
    Item& mObj;
};

}}}  // namespace scn::step::item

#endif
