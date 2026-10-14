#include "scn/step/boss/galactaknight/StateJump.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
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
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateWait.h"
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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"
#include "scn/step/weapon/Weapon.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateJump::StateJump(Boss* boss, const JumpDesc& desc)
    : StateBase(boss), mFrame(desc._C), mCount(0), mStartPos(boss->location().pos()), mGoalPos(), mIsStart(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (desc._10) {
        Utility::TurnHatedHero(obj());
    }
    mGoalPos.x = desc._4 * obj().target().getSign() + mStartPos.x;
    mGoalPos.y = desc._8 + custom.landCtrl().getFloorY();
    mGoalPos.z = desc._12 ? mStartPos.z : 0.0f;
    obj().model().reqScript(desc._0);
    if (desc._11) {
        obj().model().rotCtrl().initRotH(0.0f);
    }
    if (mStartPos.z < -4.0f) {
        obj().worldCage().setIsValid(false);
    }
    if (desc._13) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    } else {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    }
    if (desc._14) {
        obj().guard().setType(static_cast<GuardType>(1));
    }
}

StateJump::~StateJump() {
    obj().worldCage().setIsValid(true);
}

void StateJump::procAnim() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().scriptTrigger().get(1)) {
        mIsStart = true;
        if (custom.landCtrl().isGround()) {
            if (mGoalPos.y - mStartPos.y > 2.5f) {
                obj().soundSE().normal().start(0x38D);
            } else {
                obj().soundSE().normal().start(0x38C);
            }
        }
    }
    if (mIsStart && mCount < mFrame) {
        mCount++;
    }
    if (mCount == mFrame) {
        obj().brainCtrl().toValid();
    }
}

void StateJump::procMove() {
    if (mIsStart) {
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mFrame);
        f32 sin = Math::SinDegF(90.0f * t);
        f32 ease = 1.0f - (1.0f - sin) * (1.0f - sin);
        f32 rate = Math::LinearInterpolation(sin, ease, 0.5f);
        Vector3 pos;
        pos.x = Math::LinearInterpolation(mStartPos.x, mGoalPos.x, t);
        pos.y = Math::LinearInterpolation(mStartPos.y, mGoalPos.y, rate);
        pos.z = mGoalPos.z;
        obj().location().setPos(pos);
    }
}

void StateJump::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
