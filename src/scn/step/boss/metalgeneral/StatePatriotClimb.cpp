#include "scn/step/boss/metalgeneral/StatePatriotClimb.h"

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
#include "scn/step/boss/metalgeneral/StatePatriotFall.h"
#include "scn/step/boss/metalgeneral/StatePatriotLaunch.h"
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

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StatePatriotClimb::StatePatriotClimb(Boss* boss) : StateBase(boss), mIsSignaled(false) {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(0x24);
    mStartPos = obj().location().pos();
    if (custom.weaponCtrl().isHoldPatriot()) {
        mGoalPos = custom.weaponCtrl().patriotPos();
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_4);
    obj().guard().setType(static_cast<GuardType>(5));
    obj().mapColl().setValid(false);
    if (!hel::math::Math::EqZero(obj().location().pos().z)) {
        obj().model().rotCtrl().setRotHTarget(param._1E0);
    } else {
        obj().model().rotCtrl().setRotHTarget(90.0f);
    }
}

StatePatriotClimb::~StatePatriotClimb() {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().hitPoint().isDead() || !custom.weaponCtrl().isHoldPatriot()) {
        obj().mapColl().setValid(false);
        f32 diff;
        {
            g3d::NodeAccessor body = obj().model().model().nodes().at(5);
            g3d::NodeAccessor root = obj().model().model().nodes().at(0);
            diff = body.worldTrans().x - root.worldTrans().x;
        }
        hel::math::Vector3 pos = obj().location().pos();
        pos.x += diff;
        obj().location().setPos(pos);
        obj().mapColl().setValid(true);
    }
}

void StatePatriotClimb::procAnim() {
    const Param& param = obj().param().metalgeneral();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (obj().model().isAllEnd()) {
        if (!mIsSignaled) {
            mIsSignaled = true;
            custom.weaponCtrl().signalPatriot(enemy::metalgeneralpatriot::SIGNAL_KIND_1);
        } else if (custom.weaponCtrl().isPermitLaunch()) {
            obj().stateChanger().setNextState<StatePatriotLaunch, Boss*>(objPtr());
            return;
        }
    }
    if (!custom.weaponCtrl().isHoldPatriot()) {
        hel::math::Vector3 velocity = param._2B4;
        velocity.x *= obj().target().getSign();
        obj().move().setVelocity(velocity);
        obj().stateChanger().setNextState<StateFall, Boss*>(objPtr());
    }
}

void StatePatriotClimb::procMove() {
    f32 total = static_cast<f32>(obj().model().anim().totalFrame());
    f32 t = obj().model().anim().frame() / total;
    f32 rate = hel::math::Math::SinDegF(90.0f * t);
    hel::math::Vector3 pos = hel::math::Math::LinearInterpolation(mStartPos, mGoalPos, rate);
    obj().location().setPos(pos);
}

void StatePatriotClimb::procFixPos() {}

}}}}  // namespace scn::step::boss::metalgeneral
