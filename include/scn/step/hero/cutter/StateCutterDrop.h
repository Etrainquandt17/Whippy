#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERDROP_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERDROP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterDrop : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterDrop(Hero* hero);
    virtual ~StateCutterDrop();
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
