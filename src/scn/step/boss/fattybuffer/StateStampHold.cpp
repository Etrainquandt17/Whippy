#include "scn/step/boss/fattybuffer/StateStampHold.h"

#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/MapCollCtrl.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/PostureCtrl.h"
#include "scn/step/boss/fattybuffer/StateStampFall.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/hero/Manager.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

const StampParam& t_param(Boss& boss) {
    const Param& param = boss.param().fattybuffer();
    return boss.angry().isAngry() ? param.mStampAngry : param.mStamp;
}

}

StateStampHold::StateStampHold(Boss* boss, bool isChase) : StateBase(boss), mCount(0), mStartY(0.0f), mIsChase(isChase), mSpeed(0.0f) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    obj().move().resetVelocity();
    mStartY = obj().location().pos().y;
}

StateStampHold::~StateStampHold() {}

void StateStampHold::procAnim() {
    const StampParam& param = t_param(obj());
    if (mCount < param.mHoldFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateStampFall, Boss*>(objPtr());
    }
}

void StateStampHold::procMove() {
    const StampParam& param = t_param(obj());
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mHoldFrame);
    f32 s = 1.0f - Math::SinDegF(90.0f * t);
    f32 rate = 1.0f - s * (s * s);
    Vector3 pos = obj().location().pos();
    pos.y = Math::Interpolate(mStartY, mStartY + param.mHoldHeight, rate);
    if (mIsChase) {
        Vector3 myPos = obj().location().pos();
        f32 diff = obj().comp().heroManager().getNearestPlayerPos(myPos).x - myPos.x;
        int sign = diff < 0.0f ? -1 : 1;
        mSpeed += param.mChaseAccel * static_cast<f32>(sign);
        mSpeed = Math::Limit(mSpeed, param.mChaseSpeedMax);
        if (diff > 0.0f) {
            mSpeed = Math::LimitMax(mSpeed, diff);
        } else {
            mSpeed = Math::LimitMin(mSpeed, diff);
        }
        pos.x += mSpeed;
    }
    obj().location().setPos(pos);
}

void StateStampHold::procFixPos() {}

}}}}  // namespace scn::step::boss::fattybuffer
