#ifndef UTIL_ANIMCONTROLLER_H
#define UTIL_ANIMCONTROLLER_H

#include "types.h"

namespace util {

class AnimController {
public:
    AnimController(f32 totalFrame);

    f32 frame() const;
    f32 totalFrame() const;
    void setFrame(f32 frame);
    void setFrameToHead();
    void setFrameToTail();
    void updateFrame();
    void start(bool doLoop);
    void stop();
    bool isAnimEnd() const;
    void changeDoLoop(bool doLoop);

private:
    void checkAnimEnd();

    f32 mTotalFrame;
    f32 mFrame;
    f32 mFrameRate;
    bool mDoLoop;
    bool mIsAnimating;
    bool mIsLooped;
};

}  // namespace util

#endif
