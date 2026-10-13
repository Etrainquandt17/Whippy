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
    void resetIntpRateZoom();
    hel::geo::Rect getLockRectTarget() const;
    hel::geo::Rect getLockRect() const;
    hel::geo::Rect getZoomTargetRect(const hel::math::Vector2& center, f32);
    void setLock(const hel::geo::Rect& rect);
    void unsetLock();
    // TODO: the enumerators are not known; boss/mahoroabattle2/StateAppearShort passes 0.
    enum FirstZoomKind {
        FIRST_ZOOM_KIND_0,
        FIRST_ZOOM_KIND_1,
    };
    void setupFirstZoom(FirstZoomKind kind);
    void reqQuake(QuakeKind kind);
    void reqZoomQuake(ZoomQuakeKind kind);
    void addCameraTarget(const hel::math::Vector2& pos);
    void clearCameraTarget();
    bool isLocked() const;
    u32 setRotDegX(f32, f32, bool);
    void unsetRotDegX(u32 handle);
    u32 setRotDegY(f32, f32, bool);
    void unsetRotDegY(u32 handle);
    void setRotRateBGX(f32 rate);
    f32 getCullingMarginHeight() const;
    void setMainTargetOnlyMode();
    void setIntpRateLockMode(f32 rate);
    void resetIntpRateLockMode();
    void setCameraHeightMin(f32 height);
    void setCameraHeightMax(f32 height);
    bool isSetMainTarget() const;
    void setMainTarget(const hel::math::Vector2& pos);

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
