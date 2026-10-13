#ifndef SCN_STEP_HERO_NEEDLE_NEEDLE_H
#define SCN_STEP_HERO_NEEDLE_NEEDLE_H

#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class Needle : public AbilityBase {
public:
    Needle(Component& component, Hero& hero);
    virtual ~Needle();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void onStateEndCleanUp();

private:
    void resetHatVisibility();
    void resetNeedleBodyVisibility();

    bool mIsSetup;
};

}
}
}
}

#endif
