#include "scn/step/boss/bonkers/StateRainBomb.h"

#include "app/Random.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/VectorInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Custom.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateRainBomb::StateRainBomb(Boss* boss, Config config)
    : StateBase(boss), mStartCount(0), mCount(0), mEndCount(0), mBombNum(0), mBigBombIndex(0) {
    const Param& param = obj().param().bonkers();
    obj().footState().setAir();
    obj().model().reqScript(17);
    obj().move().resetVelocity();
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AC));
    if (config._0) {
        mBigBombIndex = app::Random::Rand(1, param.mRainBombNum);
    }
}

StateRainBomb::~StateRainBomb() {
    obj().objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1AB));
}

void StateRainBomb::procAnim() {
    const Param& param = obj().param().bonkers();
    if (mStartCount < param.mRainBombWait) {
        mStartCount++;
    } else if (mCount < param.mRainBombInterval * param.mRainBombNum) {
        if (mCount == param.mRainBombInterval * mBombNum) {
            mBombNum++;
            reqBomb();
        }
        mCount++;
    } else if (mEndCount < param.mRainBombWait) {
        mEndCount++;
    } else {
        obj().stateChanger().setNextState<common::StateFall, Boss*>(objPtr());
    }
}

void StateRainBomb::procMove() {}

void StateRainBomb::procFixPos() {}

void StateRainBomb::reqBomb() {
    const Param& param = obj().param().bonkers();
    Custom* custom = hel::common::DynamicCast<Custom*, ICustom>(obj().custom());
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos.y += param.mRainBombThrowOffsetY;
    hel::math::Vector2 speed(0.0f, param.mRainBombSpeedV);
    f32 sign = app::Random::Rand(10) < 5 ? 1.0f : -1.0f;
    switch (mBombNum) {
    case 1:
        speed.x = param.mRainBombSpeedSide * -obj().target().getSign();
        break;
    case 2:
        speed.x = param.mRainBombSpeedCenter * sign;
        break;
    case 3:
        speed.x = param.mRainBombSpeedSide * obj().target().getSign();
        break;
    }
    map::BinEnemySize size = mBombNum == mBigBombIndex ? map::BinEnemySize_Gigant : map::BinEnemySize_Normal;
    custom->reqBomb(pos, speed, size);
}

}
}
}
}
