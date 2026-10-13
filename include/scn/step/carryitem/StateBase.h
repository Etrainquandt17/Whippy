#ifndef SCN_STEP_CARRYITEM_STATEBASE_H
#define SCN_STEP_CARRYITEM_STATEBASE_H

#include "scn/step/carryitem/IState.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class StateBase : public IState {
public:
    StateBase(CarryItem* carryItem);
    virtual ~StateBase();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

    CarryItem& obj() const;
    CarryItem& obj();
    CarryItem* objPtr();

private:
    CarryItem& mObj;
};

}}}  // namespace scn::step::carryitem

#endif
