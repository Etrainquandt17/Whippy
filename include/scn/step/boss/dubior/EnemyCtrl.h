#ifndef SCN_STEP_BOSS_DUBIOR_ENEMYCTRL_H
#define SCN_STEP_BOSS_DUBIOR_ENEMYCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "hel/common/MutableArray.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/enemy/Accessor.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class EnemyCtrl {
public:
    EnemyCtrl(Boss& boss);

    void request(map::BinEnemyVariation variation, hel::math::Vector2 pos, hel::math::Vector3 velocity);
    void cleanup();

private:
    Boss& mBoss;
    hel::common::MutableArray<enemy::Accessor, 10> mEnemies;
};

}}}}  // namespace scn::step::boss::dubior

#endif
