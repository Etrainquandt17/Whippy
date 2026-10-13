#include "util/FrameCounter.h"

namespace util {

FrameCounter::FrameCounter()
    : mMaxFrame(0)
    , mFrame(0) {}

FrameCounter::FrameCounter(u32 maxFrame)
    : mMaxFrame(maxFrame)
    , mFrame(0) {}

void FrameCounter::reset() {
    mFrame = 0;
}

void FrameCounter::reset(u32 maxFrame) {
    mMaxFrame = maxFrame;
    reset();
}

void FrameCounter::advance() {
    mFrame++;
}

u32 FrameCounter::frame() const {
    return mFrame;
}

u32 FrameCounter::maxFrame() const {
    return mMaxFrame;
}

bool FrameCounter::isEnd() const {
    return mFrame == mMaxFrame;
}

void FrameCounter::advanceIfNotEnd() {
    if (!isEnd()) {
        advance();
    }
}

void FrameCounter::setEnd() {
    mFrame = mMaxFrame;
}

void FrameCounter::setEndIfNotEnd() {
    if (!isEnd()) {
        setEnd();
    }
}

f32 FrameCounter::normalizedFrame() const {
    if (mMaxFrame == 0) {
        return 1.0f;
    }
    return static_cast<f32>(mFrame) / static_cast<f32>(mMaxFrame);
}

f32 FrameCounter::inversedNormalizedFrame() const {
    return 1.0f - normalizedFrame();
}

}
