#ifndef SCN_STEP_WEAPON_FIGHTERKICKSHOT_STATEEXPLOSION_H
#define SCN_STEP_WEAPON_FIGHTERKICKSHOT_STATEEXPLOSION_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace fighterkickshot {

class StateExplosion : public StateBase {
public:
    StateExplosion(Weapon* weapon);
    virtual ~StateExplosion();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

private:
    u32 _8;
};

}
}
}
}

#endif
