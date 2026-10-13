#ifndef SCN_STEP_WEAPON_STARSHOTLV1_STATEMAIN_H
#define SCN_STEP_WEAPON_STARSHOTLV1_STATEMAIN_H

#include "hel/math/Direction3.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv1 {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void deadWithEffect();

private:
    f32 mRot;
    hel::math::Direction3 _C;
    f32 mScale;
};

}
}
}
}

#endif
