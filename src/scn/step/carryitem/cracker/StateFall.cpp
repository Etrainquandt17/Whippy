#include "scn/step/carryitem/cracker/StateFall.h"

#include "gobj/Location.h"
#include "scn/step/Component.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/MapColl.h"
#include "scn/step/carryitem/Utility.h"
#include "scn/step/carryitem/cracker/StateUse.h"
#include "scn/step/carryitem/cracker/Utility.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/SoundSE.h"
#include "scn/step/core/PermEffect.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

StateFall::StateFall(CarryItem* carryItem)
    : StateBase(carryItem)
    , mFallAlgorithm(*carryItem)
    , mFlashAngle(0.0f)
    , mIsExploded(false)
    , mExplodeFrame(0)
    , mShakeFrame(0) {
    obj().mapColl().setValid(true);
    if (obj().useCount() >= obj().param().cracker()._8) {
        obj().objColl().clearAttack();
        obj().objColl().setSearchHitFlagXlu(static_cast<ocoll::Flag>(2));
        obj().objColl().addSearchHit(2, 1.0f);
    }
    obj().mapColl().setIgnoreInvisibleRoof(true);
    cracker::Utility::StartFlashAnim(obj());
}

StateFall::~StateFall() {
    obj().mapColl().setValid(false);
    obj().mapColl().setIgnoreInvisibleRoof(false);
}

void StateFall::procAnim() {
    if (mIsExploded) {
        if (++mExplodeFrame == 1) {
            obj().comp().permEffect().normal().requestP(static_cast<effect::Kind>(0x33C), obj().location().pos());
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
            obj().soundSE().start(0xFF);
            obj().objColl().clearAttack();
            obj().objColl().setAttackType(static_cast<ocoll::AttackType>(0x249));
            obj().objColl().addAttack(0, 1.8f);
            obj().model().setVisibility(false);
        }
        if (mExplodeFrame >= 12) {
            obj().dead();
        }
    } else {
        mFallAlgorithm.procAnim();
        reqShake();
        mFlashAngle = cracker::Utility::UpdateFlash(obj(), mFlashAngle);
    }
}

void StateFall::procMove() {
    if (!mIsExploded) {
        mFallAlgorithm.procMove();
    }
}

void StateFall::procFixPos() {
    if (mIsExploded) {
        return;
    }
    if (obj().getUser().wasSet()) {
        obj().stateChanger().setNextState<StateUse, CarryItem*>(objPtr());
        return;
    }
    if (obj().useCount() >= obj().param().cracker()._8 && obj().mapColl().result().isHit() && !mIsExploded) {
        explode();
    } else {
        mFallAlgorithm.procFixPos();
    }
}

void StateFall::procObjCollReact() {
    if (mIsExploded) {
        return;
    }
    if (obj().useCount() >= obj().param().cracker()._8 && carryitem::Utility::IsSearchCollide(obj())) {
        explode();
    } else {
        mFallAlgorithm.procObjCollReact();
    }
}

void StateFall::explode() {
    if (!mIsExploded) {
        mIsExploded = true;
        obj().model().rotCtrl().initRotH(50.0f);
        obj().model().rotCtrl().initRotV(0.0f);
        obj().model().rotCtrl().resetRotTarget();
        carryitem::Utility::OnCrash(obj());
    }
}

void StateFall::reqShake() {
    if (obj().useCount() >= obj().param().cracker()._4) {
        mShakeFrame++;
        if (mShakeFrame == obj().param().cracker()._14) {
            obj().model().shake().request(static_cast<chara::ShakeKind>(0));
            mShakeFrame = 0;
        }
    } else {
        mShakeFrame = 0;
    }
}

}}}}  // namespace scn::step::carryitem::cracker
