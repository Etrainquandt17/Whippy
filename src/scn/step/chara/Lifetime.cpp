#include "scn/step/chara/Lifetime.h"

namespace scn {
namespace step {
namespace chara {

Lifetime::Lifetime() : mIsAgeless(true), mFrame(1) {}

void Lifetime::update() {
    if (!mIsAgeless && mFrame != 0) {
        mFrame--;
    }
}

void Lifetime::set(u32 frame) {
    mFrame = frame;
    mIsAgeless = false;
}

u32 Lifetime::get() const {
    return mFrame;
}

bool Lifetime::isDead() const {
    return mFrame == 0;
}

void Lifetime::setAgeless() {
    mIsAgeless = true;
}

void Lifetime::unsetAgeless() {
    mIsAgeless = false;
}

}
}
}
