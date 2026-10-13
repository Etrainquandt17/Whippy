#ifndef SCN_STEP_WEAPON_DEESPEAR_STATEVANISH_H
#define SCN_STEP_WEAPON_DEESPEAR_STATEVANISH_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace deespear {

class StateVanish : public StateBase {
public:
    StateVanish(Weapon* weapon, f32 rot);
    virtual ~StateVanish();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    f32 _8;
    u32 _C;
};

}
}
}
}

#endif
