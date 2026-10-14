#include "scn/step/boss/galactaknight/StateDeadEscape.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/ArenaCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/galactaknight/CollisionCtrl.h"
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
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

StateDeadEscape::StateDeadEscape(Boss* boss)
    : StateBase(boss), mCount(0), mStartPos(boss->location().pos()), mVelocity(), mDir() {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().model().reqScript(0x2C);
    obj().model().rotCtrl().initRotH(0.0f);
    mDir.mFront = Vector3::BASIS_X * obj().target().getSign();
    mDir.restructFrontUp();
    obj().worldCage().setIsValid(false);
}

StateDeadEscape::~StateDeadEscape() {}

void StateDeadEscape::procAnim() {
    const Param& param = obj().param().galactaknight();
    if (mCount < param._160) {
        mCount++;
        if (mCount == param._160) {
            if (Utility::IsArena(obj())) {
                obj().comp().bossManager().arenaCtrl().setNextScene(true);
            } else {
                obj().dead();
            }
        }
    }
}

void StateDeadEscape::procMove() {
    const Param& param = obj().param().galactaknight();
    if (mCount > param._15C) {
        Vector3 pos = obj().location().pos();
        pos += mVelocity;
        obj().location().setPos(pos);
        return;
    }
    Vector3 prevPos = obj().location().pos();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._15C);
    f32 ease = 1.0f - Math::CosDegF(90.0f * t);
    t = Math::LinearInterpolation(t, ease, 0.85f);
    f32 sin = Math::SinDegF(90.0f * t);
    f32 u = Math::LinearInterpolation(t, sin, 0.8f);
    Vector3 pos = mStartPos;
    pos.x += param._164 * Math::SinDegF(180.0f * t) * obj().target().getSign();
    pos.y += param._168 * (1.0f - Math::CosDegF(90.0f * t));
    f32 z = param._170 * (1.0f - Math::CosDegF(90.0f * u));
    pos.z += -param._16C * Math::SinDegF(270.0f * u) + z;
    obj().location().setPos(pos);
    mVelocity = pos - prevPos;
    Vector3 dir = mVelocity;
    if (!dir.isZeroLoose(0.00001f)) {
        dir.z *= 0.4f;
        dir.normalize();
        mDir.mFront = mDir.mFront.slerp(dir, 0.1f);
        mDir.mUp = Vector3::BASIS_Y;
        mDir.restructFrontUp();
    }
    f32 rot;
    if (t < 0.5f) {
        f32 r = 1.0f - Math::SinDegF(90.0f * (2.0f * t));
        rot = param._174 * (1.0f - r * r);
    } else {
        f32 v = 2.0f * (t - 0.5f);
        f32 v2 = v * v;
        f32 rate = 3.0f * v2 - 2.0f * v * v2;
        rot = Math::LinearInterpolation(param._174, param._178, rate);
    }
    rot *= -obj().target().getSign();
    mDir.mUp.rotate(mDir.mFront, 0.017453292f * rot);
    mDir.restructUpFront();
    Matrix34 mtx(mDir, Vector3::ZERO);
    obj().model().model().nodes().at(1).localMtx().setRTMtx(mtx);
}

void StateDeadEscape::procFixPos() {}

}}}}  // namespace scn::step::boss::galactaknight
