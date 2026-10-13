#include "scn/step/boss/StateBase.h"

namespace scn {
namespace step {
namespace boss {

StateBase::StateBase(Boss* boss)
    : mObj(*boss) {}

Boss& StateBase::obj() const {
    return mObj;
}

Boss& StateBase::obj() {
    return mObj;
}

Boss* StateBase::objPtr() {
    return &mObj;
}

void StateBase::procAnim() {}

void StateBase::procMove() {}

void StateBase::procConstraint() {}

void StateBase::procFixPos() {}

void StateBase::procObjCollReact() {}

StateBase::~StateBase() {}

}
}
}
