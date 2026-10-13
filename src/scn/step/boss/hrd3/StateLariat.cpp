#include "scn/step/boss/hrd3/StateLariat.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/InfoHitPointCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/PilotCtrl.h"
#include "scn/step/boss/hrd3/ShadowCtrl.h"
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/info/BossPanel.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateLariat::StateLariat(Boss* boss, u32 frame, f32 distance)
    : StateBase(boss), mCount(0), mFrame(frame), mSpeedMax(0.0f), mSpeed(0.0f), mAccel(0.0f), mDecel(0.0f), mRot(0.0f),
      mRotSpeed(0.0f), mIsMove(false) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mFrame != 0) {
        mSpeedMax = distance / static_cast<f32>(mFrame);
        mDecel = mSpeedMax / static_cast<f32>(obj().param().hrd3()._BC);
        mAccel = mDecel * obj().target().getSign();
    }
    if (custom.partsCtrl().isExistHipNeedle()) {
        obj().model().reqScript(0x18);
    } else {
        obj().model().reqScript(0x17);
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_3);
    obj().guard().setType(static_cast<GuardType>(2));
}

StateLariat::~StateLariat() {}

void StateLariat::procAnim() {
    if (obj().scriptTrigger().get(0)) {
        mIsMove = true;
        mRot = obj().model().rotCtrl().getRotH() * obj().target().getSign();
        obj().soundSE().state().start(0x3D3);
    }
    if (mIsMove && mCount < mFrame) {
        updateRotate();
        mCount++;
        if (mCount == mFrame) {
            obj().objColl().clearAttack(1);
            obj().model().reqScript(0x1A);
            mIsMove = false;
        }
    } else if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateLariat::procMove() {
    const Param& param = obj().param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    hel::math::Vector3 pos = obj().location().pos();
    if (mIsMove) {
        mSpeed = hel::math::Math::Limit(mSpeed + mAccel, mSpeedMax);
    } else {
        if (hel::math::Math::Abs(mSpeed) < mDecel) {
            mSpeed = 0.0f;
        } else {
            int sign = mSpeed < 0.0f ? -1 : 1;
            mSpeed += -mDecel * static_cast<f32>(sign);
        }
    }
    pos.x += mSpeed;
    f32 x = custom.landCtrl().getAdjustX(pos.x, param._C);
    if (x != pos.x) {
        pos.x = x;
        mAccel *= -1.0f;
        mSpeed *= -1.0f;
    }
    obj().location().setPos(pos);
}

void StateLariat::procFixPos() {}

void StateLariat::updateRotate() {
    const Param& param = obj().param().hrd3();
    mRotSpeed += param._C4;
    mRotSpeed = hel::math::Math::Limit(mRotSpeed, param._C0);
    mRot += mRotSpeed;
    if (mRot < -180.0f) {
        mRot += 360.0f;
    }
    if (mRot > 180.0f) {
        mRot -= 360.0f;
    }
    obj().model().rotCtrl().initRotH(mRot);
}

}}}}  // namespace scn::step::boss::hrd3
