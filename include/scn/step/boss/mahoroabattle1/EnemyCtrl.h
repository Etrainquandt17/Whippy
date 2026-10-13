#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_ENEMYCTRL_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_ENEMYCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

// TODO: members.
class EnemyCtrl {
public:
    struct ReqData {
        u32 _0;
        bool _4;
    };

    void addReqData(const ReqData& data);
    void clearReqData();
};

}
}
}
}

#endif
