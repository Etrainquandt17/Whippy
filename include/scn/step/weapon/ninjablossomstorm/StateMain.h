#ifndef SCN_STEP_WEAPON_NINJABLOSSOMSTORM_STATEMAIN_H
#define SCN_STEP_WEAPON_NINJABLOSSOMSTORM_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjablossomstorm {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual ~StateMain();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    int mFrame;
};

}
}
}
}

#endif
