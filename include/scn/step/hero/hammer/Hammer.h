#ifndef SCN_STEP_HERO_HAMMER_HAMMER_H
#define SCN_STEP_HERO_HAMMER_HAMMER_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace hammer {

class Hammer : public AbilityBase {
public:
    Hammer(Component& component, Hero& hero);
    virtual ~Hammer();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();

private:
    bool mIsSetup;
};

}
}
}
}

#endif
