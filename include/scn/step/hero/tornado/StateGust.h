#ifndef SCN_STEP_HERO_TORNADO_STATEGUST_H
#define SCN_STEP_HERO_TORNADO_STATEGUST_H

#include "scn/step/hero/StateBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace hero {

}
namespace weapon {
class Weapon;
}
namespace hero {
namespace tornado {

class StateGust : public StateBase {
public:
    static bool TryToChangeState(Hero* hero);

    StateGust(Hero* hero, bool isUp);
    virtual ~StateGust();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

private:
    void createWeapon();

    util::ObjRefHandle<weapon::Weapon> mWeapon;
    bool mIsUp;
    bool mIsWeaponHit;
};

}
}
}
}

#endif
