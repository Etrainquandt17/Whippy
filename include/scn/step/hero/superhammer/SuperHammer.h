#ifndef SCN_STEP_HERO_SUPERHAMMER_SUPERHAMMER_H
#define SCN_STEP_HERO_SUPERHAMMER_SUPERHAMMER_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace superhammer {

class SuperHammer : public AbilityBase {
public:
    SuperHammer(Component& component, Hero& hero);
    virtual ~SuperHammer();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();
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
