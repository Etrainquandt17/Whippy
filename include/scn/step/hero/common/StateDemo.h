#ifndef SCN_STEP_HERO_COMMON_STATEDEMO_H
#define SCN_STEP_HERO_COMMON_STATEDEMO_H

#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

class StateDemo : public StateBase {
public:
    StateDemo(Hero* hero, ScriptKind kind, bool isPauseDisable);
    virtual ~StateDemo();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    bool mIsPauseDisable;
};

}
}
}
}

#endif
