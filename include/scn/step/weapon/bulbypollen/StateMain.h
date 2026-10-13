#ifndef SCN_STEP_WEAPON_BULBYPOLLEN_STATEMAIN_H
#define SCN_STEP_WEAPON_BULBYPOLLEN_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace bulbypollen {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();
    void dead();

private:
    u32 _8;
};

}
}
}
}

#endif
