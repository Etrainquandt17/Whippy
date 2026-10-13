#ifndef SCN_STEP_HERO_SWORD_STATESWORDCHARGE_H
#define SCN_STEP_HERO_SWORD_STATESWORDCHARGE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace sword {

class StateSwordCharge : public StateBase {
public:
    StateSwordCharge(Hero* hero);
    virtual ~StateSwordCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
};

}
}
}
}

#endif
