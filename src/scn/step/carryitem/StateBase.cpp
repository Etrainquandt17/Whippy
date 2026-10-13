#include "scn/step/carryitem/StateBase.h"

namespace scn {
namespace step {
namespace carryitem {

StateBase::StateBase(CarryItem* carryItem)
    : mObj(*carryItem) {}

CarryItem& StateBase::obj() const {
    return mObj;
}

CarryItem& StateBase::obj() {
    return mObj;
}

CarryItem* StateBase::objPtr() {
    return &mObj;
}

void StateBase::procAnim() {}

void StateBase::procMove() {}

void StateBase::procConstraint() {}

void StateBase::procFixPos() {}

void StateBase::procObjCollReact() {}

StateBase::~StateBase() {}

}}}  // namespace scn::step::carryitem
