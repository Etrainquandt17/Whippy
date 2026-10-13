#ifndef SCN_STEP_HERO_SUPERSWORD_SUPERSWORD_H
#define SCN_STEP_HERO_SUPERSWORD_SUPERSWORD_H

#include "dynamics/Desc.h"
#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {

class SuperSword : public AbilityBase {
public:
    SuperSword(Component& component, Hero& hero);
    virtual ~SuperSword();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();
    virtual bool isDepleted() const;

private:
    bool mIsSetup;
    dynamics::Desc mHatDynamics;
};

}
}
}
}

#endif
