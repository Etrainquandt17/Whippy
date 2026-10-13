#include "scn/step/boss/metalgeneral/StateBeamSwordDash.h"

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
#include "scn/step/boss/metalgeneral/StatePatriotTackleUpper.h"
#include "scn/step/boss/metalgeneral/StateWait.h"
#include "scn/step/boss/metalgeneral/States.h"
#include "scn/step/boss/metalgeneral/WeaponCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
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
#include "scn/step/map/LandManager.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

StateBeamSwordDash::StateBeamSwordDash(Boss* boss) : StateBase(boss), mPhase(PHASE_0), mCount(0) {
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    obj().model().reqScript(0x11);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_2);
    Utility::ControlHateOnAction(obj());
}

StateBeamSwordDash::~StateBeamSwordDash() {
    obj().objColl().clearAttack(1);
}

void StateBeamSwordDash::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (obj().model().getCurrentScriptIndex() == 0x12 && obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
        return;
    }
    if (mPhase == PHASE_1) {
        mCount++;
        if (mCount == param._10C) {
            mPhase = PHASE_2;
            obj().effect().state().requestN(static_cast<effect::Kind>(0x460), 3);
            obj().effect().state().requestN(static_cast<effect::Kind>(0x61C), 3);
            obj().flash().attack().setEnd((GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
            reqStar();
        }
    }
    if (obj().scriptTrigger().get(0)) {
        mPhase = PHASE_1;
        f32 speed = param._108 * obj().target().getSign();
        obj().move().setSpeedH(speed);
    }
    if (obj().scriptTrigger().get(1)) {
        obj().gearManager().gear(0).setVisibility(true);
    }
    if (obj().scriptTrigger().get(2)) {
        obj().gearManager().gear(0).setVisibility(false);
    }
    if (obj().scriptTrigger().get(3)) {
        obj().effect().state().requestN(static_cast<effect::Kind>(0x471), obj().gearManager().gear(0).nodes().at(1));
    }
}

void StateBeamSwordDash::procMove() {
    const Param& param = obj().param().metalgeneral();
    gobj::MoveParamDecel zero = gobj::MoveParamDecel::Zero();
    switch (mPhase) {
    case PHASE_0:
    case PHASE_4:
        obj().move().groundDecel(param._1C);
        break;
    case PHASE_1:
        obj().move().decel(zero);
        break;
    case PHASE_2:
    case PHASE_3:
        obj().move().groundAccel(obj().target().isRightDir(), param._110);
        break;
    }
}

void StateBeamSwordDash::procFixPos() {
    const Param& param = obj().param().metalgeneral();
    hel::math::Vector2 pos = obj().location().pos().getXY();
    pos.x += param._11C * obj().target().getSign();
    if (obj().comp().mapLandManager().native().isExistLand(pos)
        || obj().comp().mapLandManager().native().isExistMoveLandInitialPlacement(pos)) {
        if (Utility::IsVariationExtra(obj()) && mPhase == PHASE_2) {
            obj().target().invert();
            mPhase = PHASE_3;
            reqStar();
        } else if (mPhase == PHASE_2 || mPhase == PHASE_3) {
            obj().model().reqScript(0x12);
            mPhase = PHASE_4;
        }
    }
}

void StateBeamSwordDash::reqStar() {
    const Param& param = obj().param().metalgeneral();
    hel::math::Vector2 pos(param._120 * obj().target().getSign(), param._124);
    hel::math::Vector2 speed(param._128 * obj().target().getSign(), param._12C);
    Utility::GenerateStarEffect(obj(), pos, speed, static_cast<map::BinEnemyVariation>(0x19B));
    obj().effect().normal().requestP(static_cast<effect::Kind>(0xB4), obj().location().pos() + pos.toVector3());
}

}
}
}
}
