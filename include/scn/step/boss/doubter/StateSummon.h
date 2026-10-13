#ifndef SCN_STEP_BOSS_DOUBTER_STATESUMMON_H
#define SCN_STEP_BOSS_DOUBTER_STATESUMMON_H

#include "scn/step/boss/StateBase.h"
#include "scn/step/map/BinEnemySize.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

class StateSummon : public StateBase {
public:
    StateSummon(Boss* boss, u32 kind, u32 num, map::BinEnemySize size);
    virtual ~StateSummon();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void reqEnemy();

    u32 mKind;
    u32 mNum;
    map::BinEnemySize mSize;
};

}
}
}
}

#endif
