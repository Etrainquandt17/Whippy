#ifndef SCN_STEP_HERO_DAMAGE_STATEBODYHIT_H
#define SCN_STEP_HERO_DAMAGE_STATEBODYHIT_H

#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/StateBase.h"

namespace scn {
namespace step {
namespace hero {
namespace damage {

class StateBodyHit : public StateBase {
public:
    StateBodyHit(Hero* hero);
    StateBodyHit(Hero* hero, ScriptKind script);
    virtual ~StateBodyHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void init(ScriptKind script);
};

}
}
}
}

#endif
