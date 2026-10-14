#include "scn/step/carryitem/stepshoe/StateFall.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "gobj/NodeRepos.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/stepshoe/StateUse.h"
#include "scn/step/carryitem/stepshoe/Utility.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/Shake.h"

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

StateFall::StateFall(CarryItem* carryItem, f32 flashAngle)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem, 0xEA)
    , mFlashAngle(flashAngle)
    , mShakeFrame(0) {
    obj().mapColl().setValid(true);
    obj().mapColl().setIgnoreInvisibleRoof(true);
    obj().model().model().nodes().at(2).localMtx().setScale(hel::math::Vector3::ALL_ONE * obj().param().stepShoe()._0);
    obj().model().reqScript(8);
    Utility::SetFlash(obj());
    mFlashAngle = Utility::UpdateBodyFlash(obj(), mFlashAngle);
    obj().setIsEnableCarry(false);
    obj().clearCheckRadiusPrevOwner();
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
    obj().mapColl().setIgnoreInvisibleRoof(false);
}

void StateFall::procAnim() {
    mFallAlgorithm.procAnim();
    mFlashAngle = Utility::UpdateBodyFlash(obj(), mFlashAngle);
    Utility::ReqFlashEffect(obj());
    reqShake();
}

void StateFall::procMove() {
    mFallAlgorithm.procMove();
    obj().setIsEnableCarry(obj().footState().isGround());
}

void StateFall::procFixPos() {
    if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*, f32>(objPtr(), mFlashAngle);
    } else if (Utility::IsDanger(obj()) && obj().mapColl().result().isHit()) {
        obj().deadWithEffect();
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
        if (mShakeFrame == obj().param().stepShoe()._30) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(1));
            mShakeFrame = 0;
        }
    } else {
        mShakeFrame = 0;
    }
}

}}}}  // namespace scn::step::carryitem::stepshoe
