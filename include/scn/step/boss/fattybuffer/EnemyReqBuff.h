#ifndef SCN_STEP_BOSS_FATTYBUFFER_ENEMYREQBUFF_H
#define SCN_STEP_BOSS_FATTYBUFFER_ENEMYREQBUFF_H

#include "hel/common/MutableArray.h"
#include "hel/math/Vec2.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

class EnemyReqBuff {
public:
    struct ReqData {
        int _0;
        hel::math::Vec2 _4;
    };

    EnemyReqBuff();

    void add(const ReqData& data);
    void clear();
    bool isEmpty() const;
    ReqData pick();

private:
    hel::common::MutableArray<ReqData, 10> mBuff;
};

}
}
}
}

#endif
