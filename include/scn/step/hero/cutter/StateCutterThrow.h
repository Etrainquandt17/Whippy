#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERTHROW_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERTHROW_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterThrow : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterThrow(Hero* hero);
    virtual ~StateCutterThrow();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool mIsHold;
};

}
}
}
}

#endif
