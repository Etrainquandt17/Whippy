#ifndef SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERRISE_H
#define SCN_STEP_HERO_CUTTER_STATECUTTERFINALCUTTERRISE_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace cutter {

class StateCutterFinalCutterRise : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateCutterFinalCutterRise(Hero* hero);
    virtual ~StateCutterFinalCutterRise();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    u32 mFrame;
    f32 _C;
    bool mIsCheckHit;
};

}
}
}
}

#endif
