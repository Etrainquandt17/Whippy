#include "scn/step/boss/fattybuffer/StateAppear.h"

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
#include "pow.h"
#include "scn/step/Component.h"
#include "scn/step/boss/BGMCtrl.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Gear.h"
#include "scn/step/boss/GearManager.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/fattybuffer/CollisionCtrl.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/Param.h"
#include "scn/step/boss/fattybuffer/StateAnger.h"
#include "scn/step/boss/fattybuffer/StateDamageL.h"
#include "scn/step/boss/fattybuffer/StateDead.h"
#include "scn/step/boss/fattybuffer/StateFirst.h"
#include "scn/step/boss/fattybuffer/StateLanding.h"
#include "scn/step/boss/fattybuffer/StateWait.h"
#include "scn/step/boss/fattybuffer/States.h"
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
using hel::math::Math;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

// TODO: a stand-in. The original reads the two members at once into temporaries ranked in text order, as it does for
// const value parameters of an inline function.
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

StateAppear::StateAppear(Boss* boss)
    : StateBase(boss)
    , mPhase(PHASE_HIDING_END)
    , mFrame(0)
    , mIsWaitDemo(true)
    , mIsGameStarted(false)
    , mIsBgmStarted(false)
    , mIsFirstAppear(false) {
    obj().footState().setGround();
    obj().mapColl().setValid(false);
    obj().invincible().setPermNoFlash();
    obj().guard().setType(static_cast<GuardType>(6));
    obj().bgmCtrl().startBossDemo();
    changePhase(mPhase);
    if (Utility::IsStagingFirstAppear(obj())) {
        Utility::StagingFirstAppearStart(obj());
        mIsFirstAppear = true;
    } else {
        mPhase = PHASE_APPEAR_JUMP;
        changePhase(PHASE_APPEAR_JUMP);
        mIsWaitDemo = false;
    }
}

StateAppear::~StateAppear() {}

void StateAppear::changePhase(Phase phase) {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(obj().custom());
    mPhase = phase;
    obj().effect().state().release();
    switch (mPhase) {
    case PHASE_APPEAR_JUMP:
        obj().footState().setAir();
        obj().model().reqScript(0x35);
        obj().shadow().setVisibility(true);
        custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
        break;
    case PHASE_APPEAR:
        obj().footState().setGround();
        Utility::TurnHatedHero(obj());
        if (mIsFirstAppear) {
            obj().model().reqScript(5);
        } else {
            obj().model().reqScript(1);
        }
        obj().mapColl().setValid(true);
        obj().worldCage().setIsValid(true);
        break;
    }
}

void StateAppear::procAnim() {
    const Param& param = obj().param().fattybuffer();
    if (Utility::IsStagingFirstAppear(obj()) && Utility::IsAppearDemoCancelRequested(obj())) {
        startGame();
        startBgm();
        obj().custom()->onStart();
        obj().mapColl().setValid(true);
        obj().worldCage().setIsValid(true);
        setupCameraLock();
        obj().shadow().setVisibility(true);
        return;
    }
    if (mIsWaitDemo) {
        if (obj().comp().heroManager().isBossDemoReady()) {
            mIsWaitDemo = false;
            obj().model().reqScript(0x34);
        }
        return;
    }
    if (obj().scriptTrigger().get(0)) {
        startGame();
    }
    if (obj().scriptTrigger().get(1)) {
        startBgm();
    }
    switch (mPhase) {
    case PHASE_HIDING_END:
        if (obj().model().isAllEnd()) {
            changePhase(PHASE_APPEAR_JUMP);
        }
        break;
    case PHASE_APPEAR_JUMP:
        mFrame++;
        if (mFrame == param.mAppearJumpFrame) {
            changePhase(PHASE_APPEAR);
        }
        break;
    case PHASE_APPEAR:
        if (obj().model().isAllEnd()) {
            setupCameraLock();
            obj().custom()->onStart();
        }
        break;
    }
}

void StateAppear::procMove() {
    const Param& param = obj().param().fattybuffer();
    Vector3 pos = obj().location().pos();
    if (mPhase == PHASE_APPEAR_JUMP) {
        f32 t = f32(mFrame + 1) / f32(param.mAppearJumpFrame);
        f32 rate = 1.0f - POW4(1.0f - Math::SinDegF(180.0f * t));
        pos.y = Math::Interpolate(
            mFrame < param.mAppearJumpFrame / 2 ? param.mAppearJumpStartHeight + obj().basePos().y : obj().basePos().y,
            param.mAppearJumpPeakHeight + obj().basePos().y, rate);
        obj().location().setPos(pos);
    }
}

void StateAppear::procFixPos() {}

void StateAppear::startGame() {
    if (!mIsGameStarted) {
        mIsGameStarted = true;
        Utility::AppearBossPanel(obj());
        if (Utility::IsStagingFirstAppear(obj())) {
            Utility::StagingFirstAppearEnd(obj());
        }
    }
}

void StateAppear::startBgm() {
    if (!mIsBgmStarted) {
        mIsBgmStarted = true;
        obj().bgmCtrl().startBossBattleNormal();
    }
}

void StateAppear::setupCameraLock() {
    const Param& param = obj().param().fattybuffer();
    Rect rect(param.mBattleCameraLockTop, param.mBattleCameraLockBottom, param.mBattleCameraLockLeft,
              param.mBattleCameraLockRight);
    t_Trans(rect, obj().basePos().x, obj().basePos().y);
    obj().comp().cameraController().setLock(rect);
    obj().comp().cameraController().resetIntpRate();
    obj().comp().cameraController().setCameraHeightMin(param.mCameraHeightMin);
}

}}}}  // namespace scn::step::boss::fattybuffer
