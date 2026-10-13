#ifndef UTIL_FRAMECOUNTER_H
#define UTIL_FRAMECOUNTER_H

#include "types.h"

namespace util {

class FrameCounter {
public:
    FrameCounter();
    FrameCounter(u32 maxFrame);

    void reset();
    void reset(u32 maxFrame);
    void advance();
    u32 frame() const;
    u32 maxFrame() const;
    bool isEnd() const;
    void advanceIfNotEnd();
    void setEnd();
    void setEndIfNotEnd();
    f32 normalizedFrame() const;
    f32 inversedNormalizedFrame() const;

private:
    u32 mMaxFrame;
    u32 mFrame;
};

}

#endif
