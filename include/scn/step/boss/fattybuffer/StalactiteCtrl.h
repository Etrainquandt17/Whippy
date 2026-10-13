#ifndef SCN_STEP_BOSS_FATTYBUFFER_STALACTITECTRL_H
#define SCN_STEP_BOSS_FATTYBUFFER_STALACTITECTRL_H

#include "hel/common/Array.h"
#include "hel/common/MutableArray.h"
#include "scn/step/enemy/Enemy.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

}
class Boss;
namespace fattybuffer {

// TODO: the types of the members at 0xC4 and 0x124.
class StalactiteCtrl {
public:
    StalactiteCtrl(Boss& boss);
    void requestUpdate();
    void setRequestData(u32 index);
    void down();
    void fall();

private:
    void requestIN(u32 index);

    Boss& mBoss;
    hel::common::Array<util::ObjRefHandle<enemy::Enemy>, 12> mEnemies;
    u32 _C4[24];
    hel::common::MutableArray<u32, 12> _124;
};

}
}
}
}

#endif
