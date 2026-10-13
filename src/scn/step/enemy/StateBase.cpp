#include "scn/step/enemy/StateBase.h"

namespace scn {
namespace step {
namespace enemy {

StateBase::StateBase(Enemy* enemy)
    : mObj(*enemy) {}

void StateBase::procAnim() {}

void StateBase::procMove() {}

void StateBase::procConstraint() {}

void StateBase::procFixPos() {}

void StateBase::procObjCollReact() {}

StateBase::~StateBase() {}

Enemy& StateBase::obj() const {
    return mObj;
}

Enemy& StateBase::obj() {
    return mObj;
}

Enemy* StateBase::objPtr() {
    return &mObj;
}

}}}  // namespace scn::step::enemy
