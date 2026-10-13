#ifndef SCN_STEP_WEAPON_GLUNKBULLET_STATEMAIN_H
#define SCN_STEP_WEAPON_GLUNKBULLET_STATEMAIN_H

#include "hel/math/Vector2.h"
#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace glunkbullet {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();

private:
    hel::math::Vector2 mStartPos;
};

}
}
}
}

#endif
