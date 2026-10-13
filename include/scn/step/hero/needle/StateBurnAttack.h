#ifndef SCN_STEP_HERO_NEEDLE_STATEBURNATTACK_H
#define SCN_STEP_HERO_NEEDLE_STATEBURNATTACK_H

#include "scn/step/hero/StateBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

class StateBurnAttack : public StateBase {
public:
    StateBurnAttack(Hero* hero);
    virtual ~StateBurnAttack();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqWeaponAll();

    u32 mFrame;
};

}
}
}
}

#endif
