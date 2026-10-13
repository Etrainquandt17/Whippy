#ifndef SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUST_H
#define SCN_STEP_HERO_SWORD_STATESWORDUNDERTHRUST_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordUnderThrust : public StateBase {
public:
    StateSwordUnderThrust(Hero* hero);
    virtual ~StateSwordUnderThrust();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
