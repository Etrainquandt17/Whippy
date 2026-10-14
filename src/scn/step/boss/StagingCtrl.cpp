#include "scn/step/boss/StagingCtrl.h"

#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {

StagingCtrl::StagingCtrl(Boss& boss) : mBoss(boss), mZoomID(0) {}

StagingCtrl::~StagingCtrl() {
    unsetZoom();
}

void StagingCtrl::initZoom(const Vector2& pos, f32 zoom) {
    unsetZoom();
    Vector2 center = mBoss.location().centerPos().getXY();
    center += pos;
    mZoomID = mBoss.comp().cameraController().setZoom(center, zoom, 1.0f);
}

void StagingCtrl::setZoom(const Vector2& pos, f32 zoom) {
    Vector2 center = mBoss.location().centerPos().getXY();
    center += pos;
    if (mZoomID != 0) {
        mBoss.comp().cameraController().updateZoom(mZoomID, center, zoom);
    } else {
        mZoomID = mBoss.comp().cameraController().setZoom(center, zoom);
    }
}

void StagingCtrl::setZoom(f32 zoom) {
    setZoom(Vector2::ZERO, zoom);
}

void StagingCtrl::unsetZoom() {
    if (mZoomID != 0) {
        mBoss.comp().cameraController().unsetZoom(mZoomID);
        mBoss.comp().cameraController().resetIntpRate();
    }
    mZoomID = 0;
}

void StagingCtrl::changeZoomIntpRate(f32 rate) {
    if (mZoomID != 0) {
        mBoss.comp().cameraController().changeZoomIntpRate(mZoomID, rate);
    }
}

}}}  // namespace scn::step::boss
