#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERCHARGE_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERCHARGE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterCharge : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterCharge(Hero* hero);
    virtual ~StateCutterCharge();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    bool _C;
};

}
}
}
}

#endif
