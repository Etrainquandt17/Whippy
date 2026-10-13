#include "scn/step/item/StateBase.h"

namespace scn {
namespace step {
namespace item {

StateBase::StateBase(Item* item)
    : mObj(*item) {}

Item& StateBase::obj() const {
    return mObj;
}

Item& StateBase::obj() {
    return mObj;
}

Item* StateBase::objPtr() {
    return &mObj;
}

void StateBase::procAnim() {}

void StateBase::procMove() {}

void StateBase::procFixPos() {}

StateBase::~StateBase() {}

}}}  // namespace scn::step::item
