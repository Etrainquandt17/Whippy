#include "scn/step/boss/goliath/CameraCtrl.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/core/MoveLimit.h"

using hel::common::DynamicCastToRef;
using hel::geo::Rect;
using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

// TODO: a stand-in, as in fattybuffer/StateFirst.cpp: the original reads the two members into temporaries ranked in
// text order. The number keeps the two uses apart, so that each is expanded.
template <int N>
inline void t_Trans(Rect& rect, const f32 x, const f32 y) {
    rect.trans(x, y);
}

}

CameraCtrl::CameraCtrl(Boss& boss)
    : mBoss(boss), mFrame(0), mTime(0), mState(0), mStartRect(), mGoalRect(), mStartLimit(), mGoalLimit(), mOffsetY(0.0f),
      mSpeedY(0.0f) {}

void CameraCtrl::update() {
    switch (mState) {
    case 1:
        updateGroundChange();
        break;
    case 2:
        updateDeadGroundChange();
        break;
    case 3:
        updateDeadGroundChangeEnd();
        break;
    }
}

void CameraCtrl::init() {
    initMoveLimit();
}

void CameraCtrl::startAppear() {
    const Param& param = mBoss.param().goliath();
    mState = 0;
    mFrame = 0;
    Rect rect(param._34, param._38, param._3C, param._40);
    t_Trans<0>(rect, mBoss.basePos().x, mBoss.basePos().y);
    mBoss.comp().cameraController().setLock(rect);
}

void CameraCtrl::startAppearEnd() {
    const Param& param = mBoss.param().goliath();
    mState = 0;
    mFrame = 0;
    Rect rect(param._44, param._48, -param._4C, param._4C);
    t_Trans<1>(rect, mBoss.basePos().x, mBoss.basePos().y);
    mBoss.comp().cameraController().setLock(rect);
    mBoss.comp().cameraController().resetIntpRate();
    f32 height = param._50 - param._54;
    mBoss.comp().cameraController().setCameraHeightMin(height);
    mBoss.comp().cameraController().setCameraHeightMax(height);
}

void CameraCtrl::startGroundChange(u32 time) {
    const Param& param = mBoss.param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    mState = 1;
    mFrame = 0;
    mTime = time;
    mStartRect = mBoss.comp().cameraController().getLockRect();
    mGoalRect = Rect(param._50, param._54, -param._58, param._58);
    mGoalRect.trans(custom.landCtrl().getCenterX(), custom.landCtrl().getFloorY());
    groundChangeCommonSetting();
}

void CameraCtrl::startDeadGroundChange() {
    const Param& param = mBoss.param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    if (mState != 2) {
        mState = 2;
        mFrame = 0;
    }
    mGoalRect = Rect(param._5C, param._60, -param._58, param._58);
    mGoalRect.trans(custom.landCtrl().getCenterX(), custom.landCtrl().getFloorY());
    groundChangeCommonSetting();
}

void CameraCtrl::initMoveLimit() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    mStartLimit = mBoss.comp().moveLimit().getLimitRect();
    mStartLimit._8 = custom.landCtrl().getCenterX() - 0.5f * custom.landCtrl().getWidth() - 1.0f;
    mStartLimit._C = 1.0f + (custom.landCtrl().getCenterX() + 0.5f * custom.landCtrl().getWidth());
    mBoss.comp().moveLimit().reset();
}

void CameraCtrl::groundChangeCommonSetting() {
    const Param& param = mBoss.param().goliath();
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    mBoss.comp().cameraController().setIntpRateLockMode(1.0f);
    mBoss.comp().cameraController().resetIntpRate();
    f32 height = param._50 - param._54;
    mBoss.comp().cameraController().setCameraHeightMin(height);
    mBoss.comp().cameraController().setCameraHeightMax(height);
    mGoalLimit = mBoss.comp().moveLimit().getLimitRect();
    mGoalLimit._8 = 0.5f + (custom.landCtrl().getCenterX() - 0.5f * custom.landCtrl().getWidth());
    mGoalLimit._C = custom.landCtrl().getCenterX() + 0.5f * custom.landCtrl().getWidth() - 0.5f;
}

void CameraCtrl::updateGroundChange() {
    const Param& param = mBoss.param().goliath();
    if (mFrame < mTime) {
        mFrame++;
    } else {
        mState = 0;
        mFrame = 0;
        initMoveLimit();
        mBoss.comp().cameraController().resetIntpRateLockMode();
        return;
    }
    f32 t = Math::InterpolationParamMinToMin(Math::InterpolationParamMinToMin(
        Math::InterpolationParamMinToMin(static_cast<f32>(mFrame) / static_cast<f32>(mTime))));
    {
        Rect rect(Math::LinearInterpolation(mStartRect._0, mGoalRect._0, t), mGoalRect._4,
                  Math::LinearInterpolation(mStartRect._8, mGoalRect._8, t),
                  Math::LinearInterpolation(mStartRect._C, mGoalRect._C, t));
        mBoss.comp().cameraController().setLock(rect);
    }
    updateMoveLimit();
}

void CameraCtrl::updateDeadGroundChange() {
    bool isEnd = false;
    if (mFrame <= 29) {
        mFrame++;
    }
    {
        Rect rect = mBoss.comp().cameraController().getLockRect();
        if (mFrame < 30) {
            mSpeedY += -0.0006f;
            mOffsetY += mSpeedY;
        }
        rect._0 += mOffsetY;
        rect._4 = mGoalRect._4;
        rect._8 = Math::LinearInterpolation(rect._8, mGoalRect._8, 0.04f);
        rect._C = Math::LinearInterpolation(rect._C, mGoalRect._C, 0.04f);
        if (rect._0 <= 2.5f + mGoalRect._0) {
            isEnd = true;
            mStartRect = rect;
        }
        mBoss.comp().cameraController().setLock(rect);
    }
    updateMoveLimit();
    if (isEnd) {
        mFrame = 0;
        mState = 3;
        mBoss.comp().moveLimit().reset();
    }
}

void CameraCtrl::updateDeadGroundChangeEnd() {
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    if (mFrame < 60) {
        mFrame++;
    }
    f32 t = static_cast<f32>(mFrame) / 60.0f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    f32 rate = 1.5f * t + t * (-0.5f * t * t);
    f32 top = Math::LinearInterpolation(mStartRect._0, mGoalRect._0, rate);
    f32 bottom = mGoalRect._4;
    f32 centerX = custom.landCtrl().getCenterX();
    f32 halfWidth = 0.5f * ((top - bottom) * mBoss.comp().mainCamera().getAspect());
    Rect rect(top, bottom, centerX - halfWidth, centerX + halfWidth);
    mBoss.comp().cameraController().setLock(rect);
}

void CameraCtrl::updateMoveLimit() {
    f32 t = static_cast<f32>(mFrame) / 20.0f;
    if (t > 1.0f) {
        t = 1.0f;
    }
    Rect rect(Math::LinearInterpolation(mStartLimit._0, mGoalLimit._0, t),
              Math::LinearInterpolation(mStartLimit._4, mGoalLimit._4, t),
              Math::LinearInterpolation(mStartLimit._8, mGoalLimit._8, t),
              Math::LinearInterpolation(mStartLimit._C, mGoalLimit._C, t));
    mBoss.comp().moveLimit().setLimitRect(rect);
}

}}}}  // namespace scn::step::boss::goliath
