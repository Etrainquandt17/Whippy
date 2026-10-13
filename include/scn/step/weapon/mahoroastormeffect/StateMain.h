#ifndef SCN_STEP_WEAPON_MAHOROASTORMEFFECT_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROASTORMEFFECT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroastormeffect {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
};

}
}
}
}

#endif
