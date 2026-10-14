#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"

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
#include "scn/step/boss/metalgeneral/StatePatriotMoveToFar.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackle.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleLower.h"
#include "scn/step/boss/metalgeneral/StatePatriotTackleUpper.h"
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

using g3d::NodeAccessor;
using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotLaunch::StatePatriotLaunch(Boss* boss) : StateBase(boss), mCount(0), mIsSignaled(false) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x25);
    if (!Math::EqZero(obj().location().pos().z)) {
        obj().model().rotCtrl().setRotHTarget(param._1E0);
    } else {
        obj().model().rotCtrl().setRotHTarget(90.0f);
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_PATRIOT);
    obj().guard().setType(static_cast<GuardType>(5));
}

StatePatriotLaunch::~StatePatriotLaunch() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().hitPoint().isDead() || !custom.weaponCtrl().isHoldPatriot()) {
        obj().mapColl().setValid(false);
        f32 diff;
        {
            NodeAccessor body = obj().model().model().nodes().at(5);
            NodeAccessor root = obj().model().model().nodes().at(0);
            diff = body.worldTrans().x - root.worldTrans().x;
        }
        Vector3 pos = obj().location().pos();
        pos.x += diff;
        obj().location().setPos(pos);
        obj().mapColl().setValid(true);
    }
}

void StatePatriotLaunch::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mCount++;
    if (!custom.weaponCtrl().isHoldPatriot()) {
        Vector3 velocity = param._2B4;
        velocity.x *= obj().target().getSign();
        obj().move().setVelocity(velocity);
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
    }
}

void StatePatriotLaunch::procMove() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (mCount > param._200) {
        if (!mIsSignaled) {
            mIsSignaled = true;
            custom.weaponCtrl().signalPatriot(enemy::metalgeneralpatriot::SIGNAL_KIND_3);
        }
        obj().move().accel(Vector3::BASIS_Y, param._204);
    } else {
        if (mCount % 5 == 0) {
            obj().comp().cameraController().reqQuake(static_cast<camera::QuakeKind>(1));
            obj().model().shake().request(static_cast<chara::ShakeKind>(0));
            custom.weaponCtrl().signalPatriot(enemy::metalgeneralpatriot::SIGNAL_KIND_2);
        }
        Vector3 pos = obj().location().pos();
        pos.y += param._1FC;
        obj().location().setPos(pos);
    }
}

void StatePatriotLaunch::procFixPos() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().location().pos().y > param._1F8 + obj().basePos().y) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_NONE);
        custom.weaponCtrl().signalPatriot(enemy::metalgeneralpatriot::SIGNAL_KIND_4);
    }
    if (obj().location().pos().y > param._1F0 + obj().basePos().y) {
        obj().stateChanger().setNextState<StatePatriotMoveToFar, Boss*>(objPtr());
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
