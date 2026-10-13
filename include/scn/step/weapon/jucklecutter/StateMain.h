#ifndef SCN_STEP_WEAPON_JUCKLECUTTER_STATEMAIN_H
#define SCN_STEP_WEAPON_JUCKLECUTTER_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace jucklecutter {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    f32 _C;
};

}
}
}
}

#endif
