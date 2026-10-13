#ifndef SCN_STEP_BOSS_LOWPER_ENEMYCTRL_H
#define SCN_STEP_BOSS_LOWPER_ENEMYCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "hel/math/Vector3.h"
#include "scn/step/enemy/Accessor.h"
#include "scn/step/enemy/lowperbullet/VariationKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}
class Boss;
namespace lowper {

class EnemyCtrl {
public:
    EnemyCtrl(Boss& boss);
    void update();
    void cleanup();
    void request(enemy::lowperbullet::VariationKind kind, hel::math::Vector3 pos, hel::math::Vector3 speed, u32 _4);
    void requestBarrier();
    void sendSignalBarrierWarpIn();
    void setBarrierAngle(f32 angle);
    void resetBarrierAngle();
    void setBarrierRadius(f32 radius);
    void resetBarrierRadius();
    f32 getBarrierRadius() const;
    void setBarrierRotSpeed(f32 speed);
    void resetBarrierRotSpeed();
    hel::math::Vector3 getBarrierFollowPos(u32 index);
    hel::math::Vector3 getBarrierFollowCenter();
    u32 getBarrierCount() const;

private:
    Boss& mBoss;
    hel::common::MutableArray<enemy::Accessor, 10> mEnemies;
    hel::common::Array<enemy::Accessor, 3> mBarriers;
    f32 mBarrierRot;
    f32 mBarrierAngle;
    f32 mBarrierAngleTarget;
    f32 mBarrierRadius;
    f32 mBarrierRotSpeed;
    bool mIsBarrierSE;
};

}}}}  // namespace scn::step::boss::lowper

#endif
