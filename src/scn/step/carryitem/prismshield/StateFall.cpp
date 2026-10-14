#include "scn/step/carryitem/prismshield/StateFall.h"

#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/prismshield/StateUse.h"
#include "scn/step/carryitem/prismshield/Utility.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/Shake.h"

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem)
    , mFlashAngle(0.0f)
    , mShakeFrame(0) {
    obj().mapColl().setValid(true);
    Utility::StartFlash(obj());
    obj().model().reqScript(0);
    mFallAlgorithm.setRotH(80.0f);
    obj().model().rotCtrl().setRotDTarget(0.0f);
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
}

void StateFall::procAnim() {
    mFallAlgorithm.procAnim();
    mFlashAngle = Utility::UpdateFlash(obj(), mFlashAngle);
    reqShake();
}

void StateFall::procMove() {
    mFallAlgorithm.procMove();
}

void StateFall::procFixPos() {
    if (Utility::IsDanger(obj()) && obj().mapColl().result().isHit()) {
        obj().deadWithEffect();
    } else if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*>(objPtr());
    } else {
        mFallAlgorithm.procFixPos();
    }
}

void StateFall::procObjCollReact() {
    mFallAlgorithm.procObjCollReact();
}

void StateFall::reqShake() {
    if (Utility::IsWarn(obj()) && !Utility::IsDanger(obj())) {
        mShakeFrame++;
        if (mShakeFrame == obj().param().prismShield()._C) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
            mShakeFrame = 0;
        }
    } else {
        mShakeFrame = 0;
    }
}

}}}}  // namespace scn::step::carryitem::prismshield
