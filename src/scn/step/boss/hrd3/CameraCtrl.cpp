#include "scn/step/boss/hrd3/CameraCtrl.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/geo/Rect.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

CameraCtrl::CameraCtrl(Boss& boss) : mBoss(boss), mCount(0) {}

void CameraCtrl::update() {
    if (mCount != 0) {
        if (--mCount == 0) {
            setMain();
        }
    }
}

void CameraCtrl::setMain() {
    const Param& param = mBoss.param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    f32 width = param._2C * mBoss.comp().mainCamera().getAspect();
    hel::geo::Rect rect(param._2C + param._30, param._30, -0.5f * width, 0.5f * width);
    rect.trans(custom.landCtrl().getCenterX(), custom.landCtrl().getFloorY());
    mBoss.comp().cameraController().unsetLock();
    mBoss.comp().cameraController().setLock(rect);
    mBoss.comp().cameraController().setCameraHeightMin(param._2C);
    mBoss.comp().cameraController().setCameraHeightMax(param._2C);
}

void CameraCtrl::setZoomOut() {
    const Param& param = mBoss.param().hrd3();
    Custom& custom = hel::common::DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    mCount = param._3C;
    f32 width = param._34 * mBoss.comp().mainCamera().getAspect();
    hel::geo::Rect rect(param._34 + param._38, param._38, -0.5f * width, 0.5f * width);
    rect.trans(custom.landCtrl().getCenterX(), custom.landCtrl().getFloorY());
    mBoss.comp().cameraController().unsetLock();
    mBoss.comp().cameraController().setLock(rect);
    mBoss.comp().cameraController().resetIntpRate();
    mBoss.comp().cameraController().setCameraHeightMin(param._34);
    mBoss.comp().cameraController().setCameraHeightMax(param._34);
}

}
}
}
}
