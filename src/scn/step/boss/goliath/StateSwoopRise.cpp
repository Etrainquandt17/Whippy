#include "scn/step/boss/goliath/StateSwoopRise.h"

#include "app/Random.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/boss/goliath/StateSwoopFall.h"
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
#include "scn/step/chara/Shake.h"
#include "scn/step/chara/WorldCage.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

StateSwoopRise::StateSwoopRise(Boss* boss, u32 time, u32 waitTime)
    : StateBase(boss), mFrame(0), mTime(time), mWaitFrame(0), mWaitTime(waitTime), mShakeWait(0) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().model().reqScript(0xF);
    mStartPos = obj().location().pos();
    Vector3 heroPos = Utility::GetHatedHeroPos(obj());
    mGoalPos.x = heroPos.x;
    mGoalPos.y = 6.5f + custom.landCtrl().getFloorY();
    mGoalPos.x = custom.landCtrl().getAdjustX(mGoalPos.x, 2.0f);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_NORMAL);
    obj().guard().setType(GUARD_TYPE_1);
}

StateSwoopRise::~StateSwoopRise() {}

void StateSwoopRise::procAnim() {
    if (mFrame < mTime) {
        mFrame++;
    } else if (mWaitFrame < mWaitTime) {
        mWaitFrame++;
    } else {
        obj().stateChanger().setNextState<StateSwoopFall, Boss*>(objPtr());
        return;
    }
    if (mFrame == mTime) {
        if (mShakeWait != 0) {
            mShakeWait--;
        } else if (mWaitTime - mWaitFrame < 30) {
            mShakeWait = 4;
            obj().model().shake().request(static_cast<chara::ShakeKind>(2));
        }
    }
}

void StateSwoopRise::procMove() {
    f32 t = static_cast<f32>(mFrame) / static_cast<f32>(mTime);
    Vector3 pos;
    f32 rateX = 0.5f * (1.0f - Math::CosDegF(180.0f * t));
    pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, rateX);
    f32 inv = 1.0f - t;
    f32 cube = inv * (inv * inv);
    f32 rateY = 1.0f - cube;
    pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rateY);
    pos.y += 0.015f * static_cast<f32>(mWaitFrame);
    obj().location().setPos(pos);
}

void StateSwoopRise::procFixPos() {}

}}}}  // namespace scn::step::boss::goliath
