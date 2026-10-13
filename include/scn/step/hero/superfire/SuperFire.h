#ifndef SCN_STEP_HERO_SUPERFIRE_SUPERFIRE_H
#define SCN_STEP_HERO_SUPERFIRE_SUPERFIRE_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace superfire {

class SuperFire : public AbilityBase {
public:
    SuperFire(Component& component, Hero& hero);
    virtual ~SuperFire();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();
    virtual bool isDepleted() const;

private:
    bool mIsSetup;
};

}
}
}
}

#endif
