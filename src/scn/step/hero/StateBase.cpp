#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {

StateBase::StateBase(Hero* hero)
    : mObj(*hero) {}

void StateBase::procAnim() {}

void StateBase::procMove() {}

void StateBase::procConstraint() {}

void StateBase::procFixPos() {}

bool StateBase::procObjCollReact() {
    return false;
}

void StateBase::procEnd() {}

StateBase::~StateBase() {}

Hero& StateBase::obj() const {
    return mObj;
}

Hero& StateBase::obj() {
    return mObj;
}

Hero* StateBase::objPtr() {
    return &mObj;
}

}}}  // namespace scn::step::hero
