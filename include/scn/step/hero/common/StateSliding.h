#ifndef SCN_STEP_HERO_COMMON_STATESLIDING_H
#define SCN_STEP_HERO_COMMON_STATESLIDING_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateSliding : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateSliding(Hero* hero);
    virtual ~StateSliding();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
};

}
}
}
}

#endif
