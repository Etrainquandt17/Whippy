#ifndef SCN_STEP_BOSS_LOWPER_MINIBLACKHOLECTRL_H
#define SCN_STEP_BOSS_LOWPER_MINIBLACKHOLECTRL_H

#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class MiniBlackHoleCtrl {
public:
    MiniBlackHoleCtrl(Boss& boss);
    ~MiniBlackHoleCtrl();
    void update();
    void set(u32 frame, f32 _2, f32 _3, f32 _4);
    void clear();
    bool canSetBlackHole(f32 x) const;

private:
    Boss& mBoss;
    u32 mFrame;
    u32 mWindId;
    util::ObjRefHandle<weapon::Weapon> mWeapon;
};

}
}
}
}

#endif
