#ifndef SCN_STEP_BOSS_WHISPY_ENEMYCTRL_H
#define SCN_STEP_BOSS_WHISPY_ENEMYCTRL_H

#define HEL_COMMON_MUTABLEARRAY_DESTRUCTOR_IN_CLASS

#include "hel/common/MutableArray.h"
#include "scn/step/enemy/Accessor.h"
#include "scn/step/map/BinEnemyKind.h"
#include "scn/step/map/BinEnemySize.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

}

class Boss;

namespace whispy {

class EnemyCtrl {
public:
    EnemyCtrl(Boss& boss);

    void request(map::BinEnemyKind kind, map::BinEnemySize size, u32 arg);
    void cleanup();
    void initXOffsTable();

private:
    Boss& mBoss;
    hel::common::MutableArray<enemy::Accessor, 10> mEnemies;
    f32 mXOffsTable[6];
    u32 mXOffsIndex;
};

}
}
}
}

#endif
