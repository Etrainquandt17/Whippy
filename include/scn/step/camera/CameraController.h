#ifndef SCN_STEP_CAMERA_CAMERACONTROLLER_H
#define SCN_STEP_CAMERA_CAMERACONTROLLER_H

#include "hel/geo/Rect.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/camera/ZoomPriority.h"
#include "scn/step/camera/ZoomQuakeKind.h"
#include "types.h"

namespace hel {
namespace math {
class Vector2;
}
}

namespace scn {
namespace step {

class Component;

namespace camera {

class CameraController {
public:
    hel::geo::Rect getDefaultWorldRect();
    u32 setZoom(const hel::math::Vector2& center, f32, f32);
    u32 setZoom(const hel::math::Vector2& center, f32);
    u32 setZoom(const hel::math::Vector2& center, f32, f32, bool);
    u32 setZoom(const hel::math::Vector2& center, f32, f32, bool, ZoomPriority priority);
    void updateZoom(u32 handle, const hel::math::Vector2& center, f32);
    void unsetZoom(u32 handle);
    void changeZoomIntpRate(u32 handle, f32 rate);
    void resetIntpRate();
    hel::geo::Rect getLockRectTarget() const;
    hel::geo::Rect getZoomTargetRect(const hel::math::Vector2& center, f32);
    void setLock(const hel::geo::Rect& rect);
    void unsetLock();
    void reqQuake(QuakeKind kind);
    void reqZoomQuake(ZoomQuakeKind kind);
    void addCameraTarget(const hel::math::Vector2& pos);
    void clearCameraTarget();
    u32 setRotDegX(f32, f32, bool);
    void unsetRotDegX(u32 handle);
    void setRotRateBGX(f32 rate);
    f32 getCullingMarginHeight() const;
    void setMainTargetOnlyMode();
    void setIntpRateLockMode(f32 rate);
    void resetIntpRateLockMode();
    void setCameraHeightMin(f32 height);
    void setCameraHeightMax(f32 height);

private:
    Component& mComponent;
    u8 _4[0x660];
    hel::geo::Rect mLockRect;
    hel::geo::Rect _674;
    bool mIsLock;
};

}
}
}

#endif
