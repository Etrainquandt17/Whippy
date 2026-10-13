#ifndef SCN_STEP_HERO_SWORD_SWORD_H
#define SCN_STEP_HERO_SWORD_SWORD_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class Sword : public AbilityBase {
public:
    Sword(Component& component, Hero& hero);
    virtual ~Sword();
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
