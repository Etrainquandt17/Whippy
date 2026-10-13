#ifndef UTIL_INTERVALTIMER_H
#define UTIL_INTERVALTIMER_H

#include "types.h"
#include "util/Delegate.h"

namespace util {

class IntervalTimer {
public:
    IntervalTimer(u32 interval) : mIsActive(false), mCount(0), mInterval(interval) {}

    void update() {
        mCount++;
        if (mCallback.isValid() && trigger()) {
            mCallback();
        }
    }

    void start(const Delegate<void(), 64>& callback) {
        mIsActive = true;
        mCount = 0;
        mCallback = callback;
    }

    bool trigger() const {
        if (!mIsActive) {
            return false;
        }
        if (mCount == 0) {
            return false;
        }
        return mCount % mInterval == 0;
    }

private:
    bool mIsActive;
    u32 mCount;
    u32 mInterval;
    Delegate<void(), 64> mCallback;
};

}  // namespace util

#endif
