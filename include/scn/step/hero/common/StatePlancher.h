#ifndef SCN_STEP_HERO_COMMON_STATEPLANCHER_H
#define SCN_STEP_HERO_COMMON_STATEPLANCHER_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StatePlancher : public StateBase {
public:
    static bool CanPlancher(Hero* hero);

    StatePlancher(Hero* hero);
    StatePlancher(Hero* hero, bool);
    virtual ~StatePlancher();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual bool procObjCollReact();

private:
    void init(bool);

    f32 mFallLength;
};

}
}
}
}

#endif
