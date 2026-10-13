#include "scn/step/boss/roah/StateAppear.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Direction3.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/mahoroaroah/BodyEffectCtrl.h"
#include "scn/step/boss/mahoroaroah/Custom.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/hero/BossDemoCtrl.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/InfoUtil.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Pinch.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "scn/step/sfx/BGFade.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateAppear::StateAppear(Boss* boss)
    : StateBase(boss), mCount(0), mMoveFrame(0), mIsMove(false), mIsWaitDemo(true), mIsStarted(false), mCameraCount(0), mIsCameraRot(false) {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    custom.mahoroaCtrl().init();
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().guard().setType(GUARD_TYPE_6);
    obj().model().setVisibility(false);
    if (Utility::IsStagingFirstAppear(obj())) {
        obj().comp().heroManager().bossDemoCtrl().startBossDemoMode(0.0f, 0.0f, hero::BossDemoCtrl::DEMO_KIND_1);
        Utility::CinemaScopeStart(obj(), static_cast<sfx::CinemaScopeKind>(0));
        mMoveFrame = param.mAppearMoveFrameFirst;
    } else {
        obj().model().reqScript(1);
        mIsWaitDemo = false;
        mMoveFrame = param.mAppearMoveFrame;
    }
}

StateAppear::~StateAppear() {}

void StateAppear::procAnim() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (Utility::IsStagingFirstAppear(obj()) && Utility::IsAppearDemoCancelRequested(obj())) {
        startGame();
        custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setInvisible();
        custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setVisible(true);
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(1));
        obj().model().setVisibility(true);
        custom.rotCtrl().setRotYMax(param.mRotYMax);
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
    {
        f32 width = param.mAppearLock.mHeight * obj().comp().mainCamera().getAspect();
        hel::geo::Rect rect(param.mAppearLock.mHeight + param.mAppearLock.mBaseY, param.mAppearLock.mBaseY,
                            -0.5f * width + param.mAppearLock.mCenterX, 0.5f * width + param.mAppearLock.mCenterX);
        f32 rate;
        if (mIsCameraRot) {
            if (mCameraCount < param.mAppearCameraInFrame) {
                mCameraCount++;
            }
            rate = static_cast<f32>(mCameraCount) / static_cast<f32>(param.mAppearCameraInFrame);
            obj().comp().mainCamera().setRotDegY(param.mAppearCameraRotY, rate);
            custom.rotCtrl().setRotYMax(90.0f);
        } else {
            if (mCameraCount != 0) {
                mCameraCount--;
            }
            rate = static_cast<f32>(mCameraCount) / static_cast<f32>(param.mAppearCameraOutFrame);
            obj().comp().mainCamera().setRotDegY(param.mAppearCameraRotY, rate);
            f32 rotY = 90.0f * rate + param.mRotYMax * (1.0f - rate);
            custom.rotCtrl().setRotYMax(rotY);
        }
        obj().comp().mainCamera().setCameraRect(rect, rate);
    }
    if (obj().scriptTrigger().get(0)) {
        startGame();
    }
    if (obj().scriptTrigger().get(1)) {
        mIsCameraRot = true;
    }
    if (obj().scriptTrigger().get(2)) {
        custom.mahoroaCtrl().getCustom().reqMotionAppearFirstWarpOut(Utility::IsStagingFirstAppear(obj()));
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(5));
        obj().comp().bgFade().setColor((GXColor){ 0xFF, 0xFF, 0xFF, 0x96 });
        obj().comp().bgFade().setFadeIn(50);
    }
    if (obj().scriptTrigger().get(3)) {
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(6));
    }
    if (obj().scriptTrigger().get(4)) {
        hel::math::Vector3 pos = obj().basePos().toVector3() + hel::math::Vector3(param.mAppearEffectOffset);
#ifdef VERSION_SUKK01
        obj().effect().state().requestPD(static_cast<effect::Kind>(0x634), pos, obj().target().getDirection3(), param.mAppearEffectScale);
#else
        obj().effect().state().requestPD(static_cast<effect::Kind>(0x633), pos, obj().target().getDirection3(), param.mAppearEffectScale);
#endif
        obj().effect().stateWarp().requestP(static_cast<effect::Kind>(0x4BC), pos);
        obj().effect().state().requestP(static_cast<effect::Kind>(0x4BD), pos);
    }
    if (obj().scriptTrigger().get(5)) {
        mIsMove = true;
        if (Utility::IsStagingFirstAppear(obj())) {
            custom.mahoroaCtrl().setScale(param.mAppearMahoroaScale);
        } else {
            custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setInvisible();
            custom.mahoroaCtrl().getCustom().bodyEffectCtrl().setVisible(true);
        }
    }
    if (obj().scriptTrigger().get(6)) {
        obj().model().setVisibility(true);
    }
    if (obj().scriptTrigger().get(7)) {
        obj().effect().state().release();
        obj().effect().stateWarp().release();
        hel::math::Vector3 pos = obj().basePos().toVector3() + hel::math::Vector3(param.mAppearEffectOffset);
        obj().effect().state().requestP(static_cast<effect::Kind>(0x4BE), pos);
    }
    if (obj().scriptTrigger().get(8)) {
        custom.mahoroaCtrl().getCustom().reqMotionAppearFirstWarpIn();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(4));
    }
    if (obj().scriptTrigger().get(9)) {
        mIsCameraRot = false;
        mCameraCount = param.mAppearCameraOutFrame;
    }
    if (obj().scriptTrigger().get(10)) {
        custom.mahoroaCtrl().getCustom().reqMotionWarpOut();
        custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(3));
        custom.mahoroaCtrl().setScale(1.0f);
    }
    if (mIsMove) {
        if (mCount < mMoveFrame) {
            mCount++;
        }
        if (mCameraCount == 0 && obj().model().isAllEnd()) {
            custom.mahoroaCtrl().setPhase(static_cast<MahoroaCtrl::Phase>(1));
            obj().custom()->onStart();
        }
    }
}

void StateAppear::procMove() {
    const Param& param = obj().param().roah();
    if (mIsMove) {
        hel::math::Vector2 start = obj().basePos() + hel::math::Vector2(param.mFirstOffset);
        hel::math::Vector2 goal = obj().basePos() + hel::math::Vector2(0.0f, param.mFirstOffset.y);
        f32 t = static_cast<f32>(mCount) / static_cast<f32>(mMoveFrame);
        f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
        hel::math::Vector2 pos = hel::math::Math::LinearInterpolation(start, goal, rate);
        obj().location().setPos(pos.toVector3());
    }
}

void StateAppear::procFixPos() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    if (param.mAppearHitX + obj().comp().mainCamera().getCenter().x > obj().location().pos().x) {
        custom.collisionCtrl().setState(CollisionCtrl::STATE_1);
    }
}

void StateAppear::startGame() {
    if (!mIsStarted) {
        mIsStarted = true;
        Utility::AppearBossPanel(obj());
        if (Utility::IsStagingFirstAppear(obj())) {
            Utility::StagingFirstAppearEnd(obj());
            obj().comp().infoManager().gameStatus().checkLowBattery(60);
            for (u32 i = 0; i < 4; i++) {
                util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromPadChan(i);
                if (hero.operator->() != 0) {
                    hero->pinch().setForbidNotifyInfo(false);
                    hero::InfoUtil::PlayerNumAppearIfNotLonely(*hero.operator->());
                }
            }
        }
    }
}

}
}
}
}
