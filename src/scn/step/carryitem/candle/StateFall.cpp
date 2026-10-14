#include "scn/step/carryitem/candle/StateFall.h"

#include "gobj/Location.h"
#include "scn/step/Component.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/candle/StateUse.h"
#include "scn/step/carryitem/candle/Utility.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/chara/Water.h"
#include "scn/step/core/PermEffect.h"

namespace scn {
namespace step {
namespace carryitem {
namespace candle {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem)
    , mWaterFrame(0) {
    Utility::ChkWater(obj());
    obj().mapColl().setValid(true);
    if (obj().useCount() == 0) {
        obj().model().reqScript(0);
    }
    obj().effectBack().release();
    if (obj().useCount() == 0) {
        obj().effectBack().requestN(static_cast<effect::Kind>(0x337), 0);
    }
    if (obj().useCount() == 0) {
        obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x248));
    }
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
}

void StateFall::procAnim() {
    if (obj().useCount() == 1 && obj().water().isInWater() && ++mWaterFrame >= 30) {
        mfBreak();
    } else {
        mFallAlgorithm.procAnim();
    }
}

void StateFall::procMove() {
    mFallAlgorithm.procMove();
}

void StateFall::procFixPos() {
    if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*>(objPtr());
    } else {
        Utility::ChkWater(obj());
        if (obj().useCount() != 0 && obj().mapColl().result().isHit()) {
            mfBreak();
        } else {
            mFallAlgorithm.procFixPos();
        }
    }
}

void StateFall::procObjCollReact() {
    mFallAlgorithm.procObjCollReact();
    if (obj().useCount() != 0 && obj().objColl().isAttackCollide()) {
        mfBreak();
    }
}

void StateFall::mfBreak() {
    hel::math::Vector3 pos = obj().location().pos();
    pos.y += 0.5f;
    obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x4B0), pos);
    obj().soundSE().start(0x100);
    obj().dead();
}

}}}}  // namespace scn::step::carryitem::candle
