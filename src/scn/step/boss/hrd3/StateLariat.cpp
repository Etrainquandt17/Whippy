#include "scn/step/boss/hrd3/StateLariat.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/hrd3/CollisionCtrl.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/StateWait.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

StateLariat::StateLariat(Boss* boss, u32 frame, f32 distance)
    : StateBase(boss), mCount(0), mFrame(frame), mSpeedMax(0.0f), mSpeed(0.0f), mAccel(0.0f), mDecel(0.0f), mRot(0.0f),
      mRotSpeed(0.0f), mIsMove(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
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
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    Vector3 pos = obj().location().pos();
    if (mIsMove) {
        mSpeed = Math::Limit(mSpeed + mAccel, mSpeedMax);
    } else {
        if (Math::Abs(mSpeed) < mDecel) {
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
    mRotSpeed = Math::Limit(mRotSpeed, param._C0);
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
