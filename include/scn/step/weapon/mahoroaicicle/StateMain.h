#ifndef SCN_STEP_WEAPON_MAHOROAICICLE_STATEMAIN_H
#define SCN_STEP_WEAPON_MAHOROAICICLE_STATEMAIN_H

#include "hel/math/Vector3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaicicle {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 mFrame;
    hel::math::Vector3 mStartPos;
    f32 mRot;
};

}
}
}
}

#endif
