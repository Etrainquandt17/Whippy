#ifndef SCN_STEP_HERO_COMMON_STATEPLANCHERHIT_H
#define SCN_STEP_HERO_COMMON_STATEPLANCHERHIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StatePlancherHit : public StateBase {
public:
    StatePlancherHit(Hero* hero);
    virtual ~StatePlancherHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    f32 mFallLength;
};

}
}
}
}

#endif
