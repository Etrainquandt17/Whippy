#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {

StateBase::StateBase(Weapon* weapon)
    : mObj(*weapon) {}

Weapon& StateBase::obj() const {
    return mObj;
}

Weapon& StateBase::obj() {
    return mObj;
}

Weapon* StateBase::objPtr() {
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
