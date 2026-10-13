#ifndef SCN_STEP_HERO_GUARD_H
#define SCN_STEP_HERO_GUARD_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

class Guard {
public:
    Guard(Hero& hero);
    ~Guard();

    void update();
    void resetAnimFrame();
    void setGuard(bool isGuard);
    bool isGuard() const;
    GXColor getColor() const;

private:
    Hero& mHero;
    bool mIsGuard;
    bool mIsFlash;
    u32 mAnimFrame;
};

}
}
}

#endif
