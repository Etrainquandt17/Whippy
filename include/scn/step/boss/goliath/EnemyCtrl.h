#ifndef SCN_STEP_BOSS_GOLIATH_ENEMYCTRL_H
#define SCN_STEP_BOSS_GOLIATH_ENEMYCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

}}  // namespace boss::goliath
namespace enemy {
class Enemy;
}
namespace boss {
class Boss;
namespace goliath {

class EnemyCtrl {
public:
    struct ReqData {
        int _0;
        f32 _4;
        f32 _8;
        bool _C;
        bool _D;
    };

    // TODO: the two members behind the handle.
    struct EnemyData {
        util::ObjRefHandle<enemy::Enemy> mEnemy;
        f32 _10;
        f32 _14;
    };

    EnemyCtrl(Boss& boss);

    void addReqData(const ReqData& data);
    ReqData pickReqData();
    void clearReqBuff();
    bool isReqBuffEmpty();
    void request();
    void throwEnemy();
    void cleanupEnemyArray();
    hel::math::Vector3 getConstraintPos() const;
    hel::math::Vector3 getEnemyInitVel(enemy::Enemy* enemy);

private:
    Boss& mBoss;
    hel::common::MutableArray<EnemyData, 8> mEnemies;
    hel::common::MutableArray<ReqData, 8> mReqBuff;
};

}}}}  // namespace scn::step::boss::goliath

#endif
