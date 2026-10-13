#ifndef SCN_STEP_BOSS_ROAH_ROTCTRL_H
#define SCN_STEP_BOSS_ROAH_ROTCTRL_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

}

class Boss;

namespace roah {

class RotCtrl {
public:
    RotCtrl(Boss& boss);

    void update();
    void toValid();
    void toInvalid();
    void setRotXMax(f32 rot);
    void setRotYMax(f32 rot);
    void setFixRotRate(f32 rate);
    f32 getRotX();
    f32 getRotY();
    void setLocalMtxTempRot(f32 x, f32 y, f32 z);
    hel::math::Vector3 getLocalMtxTempRot();
    void resetLocalMtxTempRot();

private:
    Boss& mBoss;
    f32 mRotX;
    f32 mRotXMax;
    f32 mFixRotRate;
    f32 mRotY;
    f32 mRotYMax;
    bool mIsValid;
    hel::math::Vector3 mLocalMtxTempRot;
};

}
}
}
}

#endif
