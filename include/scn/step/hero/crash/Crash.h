#ifndef SCN_STEP_HERO_CRASH_CRASH_H
#define SCN_STEP_HERO_CRASH_CRASH_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace crash {

class Crash : public AbilityBase {
public:
    Crash(Component& component, Hero& hero);
    virtual ~Crash();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();

private:
    void requestHatLight();
    void releaseHatLight();

    bool mIsSetup;
    bool mIsHatLight;
};

}
}
}
}

#endif
