#include "scn/step/boss/whispy/StateVacuum.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/boss/whispy/StateCapture.h"
#include "scn/step/boss/whispy/StateVacuumEnd.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

StateVacuum::StateVacuum(Boss* boss) : StateBase(boss), mCount(0), mEnemyTimer(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const VacuumParam& param = Utility::IsVariationExtra(obj()) ? obj().param().whispy().mVacuumExtra : obj().param().whispy().mVacuum;
    obj().model().reqScript(0x10);
    obj().guard().setType(Utility::IsVariationExtra(obj()) ? GUARD_TYPE_2 : GUARD_TYPE_3);
    obj().objColl().addSearchHit(0, param.mSearchRadius, param.mSearchOffset, param.mSearchOffset2);
    custom.windCtrl().set(param.mWindSpeed, param.mWindAccel, param.mWindSpeedMax);
}

StateVacuum::~StateVacuum() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.windCtrl().clear();
    obj().objColl().clearSearchHit();
    custom.enemyReqBuff().clear();
}

void StateVacuum::procAnim() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    const VacuumParam& param = obj().variation() == 1 ? obj().param().whispy().mVacuumExtra : obj().param().whispy().mVacuum;
    mCount++;
    if (mCount == param.mFrame) {
        obj().stateChanger().setNextState<StateVacuumEnd, Boss*>(objPtr());
        return;
    }
    if (mEnemyTimer != 0) {
        mEnemyTimer--;
        return;
    }
    if (!custom.enemyReqBuff().isEmpty()) {
        EnemyReqBuff::ReqData data = custom.enemyReqBuff().pick();
        custom.enemyCtrl().request(static_cast<map::BinEnemyKind>(data.mKind), static_cast<map::BinEnemySize>(data.mSize), data._8);
    }
    mEnemyTimer = param.mEnemyInterval;
}

void StateVacuum::procMove() {}

void StateVacuum::procObjCollReact() {
    if (hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom()).captureCtrl().checkCapture()) {
        obj().stateChanger().setNextState<StateCapture, Boss*>(objPtr());
    }
}

}
}
}
}
