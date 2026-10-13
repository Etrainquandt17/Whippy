#ifndef SCN_STEP_BOSS_GOLIATH_ENEMYCTRL_H
#define SCN_STEP_BOSS_GOLIATH_ENEMYCTRL_H

#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

// TODO: members.
class EnemyCtrl {
public:
    struct ReqData {
        int _0;
        f32 _4;
        f32 _8;
        bool _C;
        bool _D;
    };

    void addReqData(const ReqData& data);
    void clearReqBuff();
};

}
}
}
}

#endif
