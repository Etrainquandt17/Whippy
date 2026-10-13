#ifndef SCN_STEP_HERO_STONE_STATEEND_H
#define SCN_STEP_HERO_STONE_STATEEND_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace stone {

class StateEnd : public StateBase {
public:
    StateEnd(Hero* hero);
    virtual ~StateEnd();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
