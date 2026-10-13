#ifndef SCN_STEP_HERO_DAMAGE_STATESPARKLV1_H
#define SCN_STEP_HERO_DAMAGE_STATESPARKLV1_H

#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateSparkLv1 : public StateBase {
public:
    StateSparkLv1(Hero* hero);
    virtual ~StateSparkLv1();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
