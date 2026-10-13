#ifndef SCN_STEP_WEAPON_COMBINATIONMETABEAM_STATEMAIN_H
#define SCN_STEP_WEAPON_COMBINATIONMETABEAM_STATEMAIN_H

#include "scn/step/weapon/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationmetabeam {

class StateMain : public StateBase {
public:
    StateMain(Weapon* weapon);
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    u32 _8;
    f32 _C;
    bool _10;
};

}
}
}
}

#endif
