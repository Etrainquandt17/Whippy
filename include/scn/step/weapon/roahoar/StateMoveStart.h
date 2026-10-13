#ifndef SCN_STEP_WEAPON_ROAHOAR_STATEMOVESTART_H
#define SCN_STEP_WEAPON_ROAHOAR_STATEMOVESTART_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

class StateMoveStart : public StateBase {
public:
    StateMoveStart(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    u32 mStartFrame;
};

}
}
}
}

#endif
