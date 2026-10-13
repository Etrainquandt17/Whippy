#ifndef SCN_STEP_BOSS_ROAH_MAHOROACTRL_H
#define SCN_STEP_BOSS_ROAH_MAHOROACTRL_H

#include "hel/math/Vector3.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

}
class Boss;
namespace mahoroaroah {
class Custom;
}
namespace roah {

// TODO: the names of the enumerators.
class MahoroaCtrl {
public:
    enum Phase {
        PHASE_0,
        PHASE_11 = 11,
    };

    MahoroaCtrl(Boss& boss);
    void init();
    void update();
    void setPhase(Phase phase);
    Phase getPhase();
    mahoroaroah::Custom& getCustom();
    void setScale(f32 scale);
    void setPos(hel::math::Vector3 pos, f32 rate);

private:
    void updatePursuit();
    void updateFirstWarpIn();
    void updateFirstWarpOut();
    void updateWait();
    void updateAppear();
    void updateEscapeMove();
    void updateEscapeWarpIn();
    void updateEscapeWarpOut();
    void initPhaseEscapeMoveFirst();
    void initPhaseEscapeMoveSecond();
    hel::math::Vector3 nextEscapeWarpPos();

    Boss& mBoss;
    util::ObjRefHandle<Boss> mMahoroa;
    Phase mPhase;
    u32 mAppearCount;
    u32 mEscapeCount;
    hel::math::Vector3 mEscapeStart;
    hel::math::Vector3 mEscapeGoal;
    u32 mEscapeWarpCount;
    f32 mPrevCameraX;
};

}
}
}
}

#endif
