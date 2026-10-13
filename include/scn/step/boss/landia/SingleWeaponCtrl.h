#ifndef SCN_STEP_BOSS_LANDIA_SINGLEWEAPONCTRL_H
#define SCN_STEP_BOSS_LANDIA_SINGLEWEAPONCTRL_H

#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

}
namespace boss {

class Boss;

namespace landia {

// TODO: members.
class SingleWeaponCtrl {
public:
    SingleWeaponCtrl(Boss& boss);

    void onFinishFormationPass();
    void onFinishGrandCross();
    util::ObjRefHandle<weapon::Weapon> weaponPtr(u32 index);
    void changeStateMoveFormationPass();
    void changeStateFinishFormationPass();
};

}
}
}
}

#endif
