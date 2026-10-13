#ifndef SCN_STEP_WEAPON_FATTYBUFFERCANNONSPLASH_STATEMAIN_H
#define SCN_STEP_WEAPON_FATTYBUFFERCANNONSPLASH_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace fattybuffercannonsplash {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
};

}
}
}
}

#endif
