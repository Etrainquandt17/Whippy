#include "scn/step/boss/metalgeneral/StateAppear.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
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
#include "scn/step/core/BGMController.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/weapon/Manager.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

// TODO: a stand-in, as in fattybuffer/StateFirst.cpp: the original reads the two members into temporaries ranked in
// text order, as it does for const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateAppear::StateAppear(Boss* boss) : StateBase(boss), mIsWaitDemo(true), mIsStarted(false), mIsBgmStarted(false) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setGround();
    Utility::TurnNearestHero(obj());
    if (!Utility::IsArena(obj())) {
        obj().comp().bgmController().pause(core::BGM_CATEGORY_0);
    }
    custom.collisionCtrl().setState(CollisionCtrl::STATE_REFLECT);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    if (Utility::IsStagingFirstAppear(obj())) {
        Utility::StagingFirstAppearStart(obj());
    } else {
        obj().model().reqScript(1);
        mIsWaitDemo = false;
    }
}

StateAppear::~StateAppear() {}

void StateAppear::procAnim() {
    const Param& param = obj().param().metalgeneral();
    if (Utility::IsStagingFirstAppear(obj()) && Utility::IsAppearDemoCancelRequested(obj())) {
        startGame();
        startBgm();
        obj().custom()->onStart();
        return;
    }
    if (mIsWaitDemo) {
        if (obj().comp().heroManager().isBossDemoReady()) {
            mIsWaitDemo = false;
            obj().model().reqScript(6);
        }
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        startGame();
    }
    if (obj().scriptTrigger().get(1)) {
        startBgm();
    }
    if (obj().model().isAllEnd()) {
        Rect rect(param._88, param._8C, param._90, param._94);
        t_Trans(rect, obj().basePos().x, obj().basePos().y);
        obj().comp().cameraController().setLock(rect);
        obj().comp().cameraController().resetIntpRate();
        obj().custom()->onStart();
    }
}

void StateAppear::procMove() {}

void StateAppear::procFixPos() {}

void StateAppear::startGame() {
    if (!mIsStarted) {
        mIsStarted = true;
        Utility::AppearBossPanel(obj());
        if (Utility::IsStagingFirstAppear(obj())) {
            Utility::StagingFirstAppearEnd(obj());
        }
    }
}

void StateAppear::startBgm() {
    if (!mIsBgmStarted) {
        mIsBgmStarted = true;
        if (!Utility::IsArena(obj())) {
            obj().comp().bgmController().request(static_cast<core::BGMCategory>(1), 6, false);
        }
    }
}

}}}}  // namespace scn::step::boss::metalgeneral
