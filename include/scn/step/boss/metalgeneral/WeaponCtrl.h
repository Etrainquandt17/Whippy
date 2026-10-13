#ifndef SCN_STEP_BOSS_METALGENERAL_WEAPONCTRL_H
#define SCN_STEP_BOSS_METALGENERAL_WEAPONCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "g3d/NodeAccessor.h"
#include "hel/common/MutableArray.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/metalgeneralball/SignalKind.h"
#include "scn/step/enemy/metalgeneralmissile/StateSpread.h"
#include "scn/step/enemy/metalgeneralpatriot/SignalKind.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

}
class Boss;
namespace metalgeneral {

class WeaponCtrl {
public:
    WeaponCtrl(Boss& boss);

    void update();
    void reqBit(hel::math::Vector2 pos, u32 num);
    void reqBomb(hel::math::Vector2 pos, hel::math::Vector2 speed, bool isBig);
    void reqMissile(hel::math::Vector2 pos, enemy::metalgeneralmissile::StateSpread::SpreadKind kind);
    void reqBall();
    void generateBall(u32 index);
    void signalBall(enemy::metalgeneralball::SignalKind kind);
    void cleanupBall();
    bool isHoldBall();
    void reqNeedlePlus();
    void reqNeedleSlant();
    void reqNeedleAll();
    void generateNeedle(f32 angle);
    void reqPatriot(hel::math::Vector3 pos, u32 loopNumMax, bool isSingle, u32 kind);
    g3d::NodeAccessor getFollowNode();
    bool isHoldPatriot();
    hel::math::Vector3 patriotPos();
    void signalPatriot(enemy::metalgeneralpatriot::SignalKind kind);
    bool isPermitLaunch();
    u32 patriotLoopCount() const;
    void setPatriotLoopCount(u32 count);
    u32 patriotLoopNumMax() const;
    void cleanupPatriotSingle();
    u32 patriotSingleCount();

private:
    Boss& mBoss;
    hel::common::MutableArray<util::ObjRefHandle<enemy::Enemy>, 6> mBalls;
    u32 mNeedlePlusCount;
    u32 mNeedleSlantCount;
    u32 mBallCount;
    util::ObjRefHandle<enemy::Enemy> mPatriot;
    hel::common::MutableArray<util::ObjRefHandle<enemy::Enemy>, 2> mPatriotSingles;
    u32 mPatriotLoopCount;
    u32 mPatriotLoopNumMax;
};

}
}
}
}

#endif
