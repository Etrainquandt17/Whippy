#ifndef SCN_STEP_WEAPON_GRANDLOWPERSPARKSHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_GRANDLOWPERSPARKSHOT_STATEMAIN_H

#include "scn/step/chara/Lifetime.h"
#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace grandlowpersparkshot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    chara::Lifetime mLifetime;
};

}
}
}
}

#endif
