#include "gobj/FootState.h"

namespace gobj {

FootState::FootState()
    : mIsGround(false) {}

bool FootState::isGround() const {
    return mIsGround;
}

bool FootState::isAir() const {
    return !mIsGround;
}

void FootState::setGround() {
    mIsGround = true;
}

void FootState::setAir() {
    mIsGround = false;
}

}  // namespace gobj
