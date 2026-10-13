#ifndef SCN_STEP_HERO_SUPERBEAM_SUPERBEAM_H
#define SCN_STEP_HERO_SUPERBEAM_SUPERBEAM_H

#include "dynamics/Desc.h"
#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace superbeam {

class SuperBeam : public AbilityBase {
public:
    SuperBeam(Component& component, Hero& hero);
    virtual ~SuperBeam();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void procAnim();
    virtual bool isDepleted() const;

private:
    bool mIsSetup;
    dynamics::Desc mHatDynamicsL;
    dynamics::Desc mHatDynamicsR;
};

}
}
}
}

#endif
