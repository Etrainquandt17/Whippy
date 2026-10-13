#ifndef SCN_STEP_WEAPON_MISSILEEXP_STATEMAIN_H
#define SCN_STEP_WEAPON_MISSILEEXP_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace missileexp {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();

private:
    u32 mFrame;
};

}
}
}
}

#endif
