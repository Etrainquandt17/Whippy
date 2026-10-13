#ifndef SCN_STEP_BOSS_GALACTAKNIGHT_STATEREVOLUTIONSWORD_H
#define SCN_STEP_BOSS_GALACTAKNIGHT_STATEREVOLUTIONSWORD_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

class StateRevolutionSword : public StateBase {
public:
    StateRevolutionSword(Boss* boss);
    virtual ~StateRevolutionSword();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqRevolutionSword();
    util::ObjRefHandle<weapon::Weapon> mWeapon;
    bool mIsRequested;
};

}
}
}
}

#endif
