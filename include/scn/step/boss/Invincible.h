#ifndef SCN_STEP_BOSS_INVINCIBLE_H
#define SCN_STEP_BOSS_INVINCIBLE_H

#include "revolution/gx/GXStruct.h"
#include "scn/step/chara/Invincible.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class Invincible {
public:
    Invincible(Boss& boss);

    void update();
    void setPerm();
    void setPermNoFlash();
    void unsetPerm();
    bool isInvincible() const;

private:
    Boss& mBoss;
    chara::Invincible mInvincible;
    GXColor mColor;
    bool mIsNoFlash;
};

}
}
}

#endif
