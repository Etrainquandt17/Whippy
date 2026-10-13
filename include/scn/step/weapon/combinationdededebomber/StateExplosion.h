#ifndef SCN_STEP_WEAPON_COMBINATIONDEDEDEBOMBER_STATEEXPLOSION_H
#define SCN_STEP_WEAPON_COMBINATIONDEDEDEBOMBER_STATEEXPLOSION_H

#include "scn/step/ocoll/AttackType.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdededebomber {

class StateExplosion : public StateBase {
public:
    StateExplosion(Weapon* weapon);
    virtual ~StateExplosion();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    f32 attackRadius() const;
    const ocoll::AttackType& attackType() const;

private:
    u32 _8;
    s32 _C;
};

}
}
}
}

#endif
