#include "scn/step/boss/roah/StateFirst.h"

#include "gobj/FootState.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/roah/Custom.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/boss/roah/StateAppear.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/info/InfoGameStatus.h"
#include "scn/step/info/Manager.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

StateFirst::StateFirst(Boss* boss) : StateBase(boss), mCount(0), mStartRect(), mGoalRect() {
    const Param& param = obj().param().roah();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(obj().custom());
    obj().footState().setAir();
    obj().model().reqScript(5);
    custom.collisionCtrl().setState(CollisionCtrl::STATE_0);
    obj().target().setIsRightDir(false);
    obj().location().setPos((obj().basePos() + hel::math::Vector2(param.mFirstOffset)).toVector3());
    {
        f32 width = param.mFirstLockStart.mHeight * obj().comp().mainCamera().getAspect();
        mStartRect = hel::geo::Rect(param.mFirstLockStart.mHeight + param.mFirstLockStart.mBaseY, param.mFirstLockStart.mBaseY,
                                    -0.5f * width + param.mFirstLockStart.mCenterX, 0.5f * width + param.mFirstLockStart.mCenterX);
    }
    {
        f32 width = param.mFirstLockGoal.mHeight * obj().comp().mainCamera().getAspect();
        mGoalRect = hel::geo::Rect(param.mFirstLockGoal.mHeight + param.mFirstLockGoal.mBaseY, param.mFirstLockGoal.mBaseY,
                                   -0.5f * width + param.mFirstLockGoal.mCenterX, 0.5f * width + param.mFirstLockGoal.mCenterX);
    }
    obj().comp().cameraController().setLock(mStartRect);
    obj().comp().cameraController().setIntpRateLockMode(1.0f);
    obj().comp().heroManager().setHidDisable();
    for (u32 i = 0; i < 4; i++) {
        util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromPadChan(i);
        if (hero.isAlive()) {
            hero->stateChecker().setDemo(true);
        }
    }
    if (Utility::IsStagingFirstAppear(obj())) {
        obj().comp().infoManager().gameStatus().startAnimOut();
    }
}

StateFirst::~StateFirst() {
    obj().comp().heroManager().setHidEnable();
    for (u32 i = 0; i < 4; i++) {
        util::ObjRefHandle<hero::Hero> hero = obj().comp().heroManager().searchHeroFromPadChan(i);
        if (hero.isAlive()) {
            hero->stateChecker().setDemo(false);
        }
    }
    obj().comp().cameraController().resetIntpRateLockMode();
}

void StateFirst::procAnim() {
    const Param& param = obj().param().roah();
    if (mCount < param.mFirstFrame) {
        mCount++;
    } else {
        obj().stateChanger().setNextState<StateAppear, Boss*>(objPtr());
    }
}

void StateFirst::procMove() {
    const Param& param = obj().param().roah();
    f32 t = static_cast<f32>(mCount) / static_cast<f32>(param.mFirstFrame);
    f32 rate = 3.0f * (t * t) - 2.0f * t * (t * t);
    hel::geo::Rect rect(hel::math::Math::LinearInterpolation(mStartRect._0, mGoalRect._0, rate),
                        hel::math::Math::LinearInterpolation(mStartRect._4, mGoalRect._4, rate),
                        hel::math::Math::LinearInterpolation(mStartRect._8, mGoalRect._8, rate),
                        hel::math::Math::LinearInterpolation(mStartRect._C, mGoalRect._C, rate));
    obj().comp().cameraController().setLock(rect);
}

void StateFirst::procFixPos() {}

}}}}  // namespace scn::step::boss::roah
