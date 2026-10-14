#include "scn/step/boss/metalgeneral/StatePatriotTackleUpper.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/NodeRepos.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "scn/step/Component.h"
#include "scn/step/boss/AttackFlash.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/metalgeneral/Custom.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/boss/metalgeneral/ScriptKind.h"
#include "scn/step/boss/metalgeneral/StateAnger.h"
#include "scn/step/boss/metalgeneral/StateAppear.h"
#include "scn/step/boss/metalgeneral/StateCircling.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlight.h"
#include "scn/step/boss/metalgeneral/StateCirclingFlightEnd.h"
#include "scn/step/boss/metalgeneral/StateDamageL.h"
#include "scn/step/boss/metalgeneral/StateDead.h"
#include "scn/step/boss/metalgeneral/StateDeadJump.h"
#include "scn/step/boss/metalgeneral/StateFall.h"
#include "scn/step/boss/metalgeneral/StateFirst.h"
#include "scn/step/boss/metalgeneral/StateLanding.h"
#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"
#include "scn/step/boss/metalgeneral/StatePatriotFall.h"
#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"
#include "scn/step/boss/metalgeneral/StatePatriotMoveToFar.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackle.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleLower.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/boss/metalgeneral/States.h"
#include "scn/step/boss/metalgeneral/WeaponCtrl.h"
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
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/map/LandManager.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Direction3;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotTackleUpper::StatePatriotTackleUpper(Boss* boss, Direction3 dir)
    : StateBase(boss), mCount(0), mWaitCount(0), mDir(dir) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x25);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().model().rotCtrl().initRotH(0.0f);
    obj().move().resetVelocity();
    mStartPos = obj().location().pos();
    mGoalPos = obj().location().pos() + Vector3(param._27C);
    f32 slide = param._27C.z * (mDir.mFront.x / mDir.mFront.z);
    mGoalPos.x += slide * param._288;
    custom.weaponCtrl().cleanupPatriotSingle();
}

StatePatriotTackleUpper::~StatePatriotTackleUpper() {
    obj().model().model().nodes().at(0).localMtx().reset();
}

void StatePatriotTackleUpper::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount < param._274) {
        mCount++;
    } else {
        u32 wait = custom.weaponCtrl().patriotSingleCount() != 0 ? param._28C : param._290;
        if (mWaitCount < wait) {
            mWaitCount++;
        } else {
            u32 loopCount = custom.weaponCtrl().patriotLoopCount() + 1;
            if (loopCount == custom.weaponCtrl().patriotLoopNumMax()) {
                custom.weaponCtrl().setPatriotLoopCount(0);
                obj().stateChanger().setNextState<StatePatriotFall, Boss*>(objPtr());
            } else {
                custom.weaponCtrl().setPatriotLoopCount(loopCount);
                obj().stateChanger().setNextState<StatePatriotMoveToFar, Boss*>(objPtr());
            }
        }
    }
}

void StatePatriotTackleUpper::procMove() {
    const Param& param = obj().param().metalgeneral();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param._274);
    Vector3 pos = Math::LinearInterpolation(mStartPos, mGoalPos, t);
    pos.y -= Math::SinDegF(180.0f * t) * param._278;
    obj().location().setPos(pos);
    Matrix34 dirMtx(mDir, Vector3::ZERO);
    f32 cos = Math::CosDegF(90.0f * t);
    f32 rot = -60.0f * (1.0f - cos);
    obj().model().model().nodes().at(0).localMtx().setRTMtx(
        Matrix34::CreateRotXYZDeg(Vector3(rot, 0.0f, 0.0f)) * dirMtx
        * Matrix34::CreateRotXYZDeg(Vector3(90.0f, 0.0f, 0.0f))
    );
}

void StatePatriotTackleUpper::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
