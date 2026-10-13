#ifndef SCN_STEP_HERO_COMMON_STATEWAIT_H
#define SCN_STEP_HERO_COMMON_STATEWAIT_H

#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateWait : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);
    static bool TryToChangeStateWithScript(Hero* hero, ScriptKind script);

    StateWait(Hero* hero);
    StateWait(Hero* hero, ScriptKind script);
    virtual ~StateWait();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void construct();

    ScriptKind mScript;
};

}
}
}
}

#endif
