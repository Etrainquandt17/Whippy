#include "scn/step/boss/whispy/StateFallEnemy.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateFallEnemy::StateFallEnemy(Boss* boss, ScriptKind kind, u32 interval)
    : StateBase(boss), mInterval(interval), mTimer(boss->param().whispy().mFallEnemyInterval) {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyCtrl().initXOffsTable();
    obj().model().reqScript(kind);
}

StateFallEnemy::~StateFallEnemy() {
    hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).enemyReqBuff().clear();
}

void StateFallEnemy::procAnim() {
    if (mTimer != 0) {
        mTimer--;
    }
    if (mTimer == 0) {
        if (!reqEnemy()) {
            obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
            return;
        }
        mTimer = mInterval;
    }
    if (obj().model().isAllEnd()) {
        obj().model().reqScript(0);
    }
}

void StateFallEnemy::procMove() {}

void StateFallEnemy::procFixPos() {}

bool StateFallEnemy::reqEnemy() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (custom.enemyReqBuff().isEmpty()) {
        return false;
    }
    EnemyReqBuff::ReqData data = custom.enemyReqBuff().pick();
    custom.enemyCtrl().request(static_cast<map::BinEnemyKind>(data.mKind), static_cast<map::BinEnemySize>(data.mSize), data._8);
    return true;
}

}
}
}
}
