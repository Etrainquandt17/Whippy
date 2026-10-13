#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_ENEMYCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_ENEMYCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

// TODO: members.
class EnemyCtrl {
public:
    struct ReqData {
        u32 _0;
        u32 _4;
    };

    void addReqData(const ReqData& data);
    void clearReqData();
};

}
}
}
}

#endif
