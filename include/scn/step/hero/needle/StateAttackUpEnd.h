#ifndef SCN_STEP_HERO_NEEDLE_STATEATTACKUPEND_H
#define SCN_STEP_HERO_NEEDLE_STATEATTACKUPEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class StateAttackUpEnd : public StateBase {
public:
    StateAttackUpEnd(Hero* hero);
    virtual ~StateAttackUpEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}
}
}
}

#endif
