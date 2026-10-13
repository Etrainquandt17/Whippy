#ifndef SCN_STEP_BOSS_GRANDLOWPER_ENEMYGENCTRL_H
#define SCN_STEP_BOSS_GRANDLOWPER_ENEMYGENCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace map {

// TODO: belongs in scn/step/map/BinEnemyKind.h, with its values.
#ifndef SCN_STEP_MAP_BINENEMYKIND_H
#define SCN_STEP_MAP_BINENEMYKIND_H
enum BinEnemyKind {
    BinEnemyKind_0,
};
#endif

}

namespace boss {
namespace grandlowper {

// TODO: members.
class EnemyGenCtrl {
public:
    void addReqData(map::BinEnemyKind kind, bool _1);
    void clearReqData();
    void shuffleReqData();
};

}
}
}
}

#endif
