#ifndef SCN_STEP_WEAPON_NINJAWAVESHOT_STATEMAIN_H
#define SCN_STEP_WEAPON_NINJAWAVESHOT_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjawaveshot {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    void setAttack();

    u32 mFrame;
    u32 mCount;
};

}
}
}
}

#endif
