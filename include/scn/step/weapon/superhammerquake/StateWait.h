#ifndef SCN_STEP_WEAPON_SUPERHAMMERQUAKE_STATEWAIT_H
#define SCN_STEP_WEAPON_SUPERHAMMERQUAKE_STATEWAIT_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace superhammerquake {

class StateWait : public StateBase {
public:
    StateWait(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 mFrame;
};

}
}
}
}

#endif
