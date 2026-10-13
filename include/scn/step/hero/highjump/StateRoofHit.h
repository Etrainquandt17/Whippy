#ifndef SCN_STEP_HERO_HIGHJUMP_STATEROOFHIT_H
#define SCN_STEP_HERO_HIGHJUMP_STATEROOFHIT_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

class StateRoofHit : public StateBase {
public:
    StateRoofHit(Hero* hero);
    virtual ~StateRoofHit();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
};

}
}
}
}

#endif
