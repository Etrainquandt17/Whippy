#ifndef SCN_STEP_CAMERA_MAINCAMERA_H
#define SCN_STEP_CAMERA_MAINCAMERA_H

#include "hel/geo/Rect.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/camera/ParamAccessor.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace camera {

class MainCamera {
public:
    MainCamera(Component& component);

    hel::math::Matrix34 viewMtx() const;
    hel::math::Vector3 viewTargetPos() const;
    hel::math::Vector3 viewEyePos() const;
    hel::math::Matrix34 originalViewMtx() const;
    hel::math::Vector3 originalViewTargetPos() const;
    hel::math::Vector3 originalViewEyePos() const;
    hel::math::Vector2 getCenter() const;
    hel::math::Vector2 getCenterBG() const;
    hel::math::Vector2 getCenterCulling() const;
    void setDistance(f32 distance);
    f32 getDistance() const;
    void setTargetDistance(f32 distance);
    f32 getTargetDistance() const;
    void setPreDistance(f32 distance);
    f32 getPreDistance() const;
    void setTargetFrame(int frame);
    int getTargetFrame() const;
    void setTargetCurrentFrame(int frame);
    int getTargetCurrentFrame() const;
    f32 getNear() const;
    f32 getNearBG() const;
    f32 getNearDistance() const;
    f32 getFar() const;
    f32 getFarBG() const;
    void setNear(f32 value);
    void setNearBG(f32 value);
    void setNearDistance(f32 value);
    void setFar(f32 value);
    void setFarBG(f32 value);
    f32 getAspect() const;
    f32 getFovy() const;
    f32 getBaseFovy() const;
    void setCameraRect(const hel::geo::Rect& rect, f32 rate);
    void setCameraRectFirstZoom(const hel::geo::Rect& rect, f32 rate, const hel::geo::Rect& zoomRect, f32 zoomRate);
    void setCameraRectBG(const hel::geo::Rect& rect, f32 rate);
    void setCameraRectCulling(const hel::geo::Rect& rect, f32 rate);
    void initWorldRect(const hel::geo::Rect& rect);
    void setWorldRect(const hel::geo::Rect& rect);
    hel::geo::Rect getWorldRect() const;
    hel::geo::Rect getWorldRectBG() const;
    hel::geo::Rect getViewRect() const;
    hel::geo::Rect getViewRectBG() const;
    f32 getRotDegX() const;
    void setRotDegX(f32 deg);
    void setRotDegX(f32 deg, f32 rate);
    f32 getRotDegY() const;
    void setRotDegY(f32 deg);
    void setRotDegY(f32 deg, f32 rate);
    const hel::math::Vector2& getOffset() const;
    const hel::math::Vector2& getOffsetBG() const;
    void setOffset(const hel::math::Vector2& offset);
    void setZoomOffset(f32 offset);
    void setOffsetBG(const hel::math::Vector2& offset);
    hel::math::Vector2 getLocationRateVec() const;
    void setIsWorldRectValid(bool isValid);
    void setIsReverseMode(bool isReverse);
    bool isReverseMode() const;

private:
    ParamAccessor mParam;
    hel::geo::Rect _8;
    hel::geo::Rect _18;
    hel::geo::Rect _28;
    f32 _38;
    f32 _3C;
    f32 _40;
    s32 _44;
    s32 _48;
    f32 _4C;
    f32 _50;
    f32 _54;
    f32 _58;
    f32 _5C;
    hel::geo::Rect _60;
    hel::geo::Rect _70;
    f32 _80;
    f32 _84;
    f32 _88;
    f32 _8C;
    hel::math::Vector2 _90;
    f32 _98;
    hel::math::Vector2 _9C;
    bool _A4;
    bool _A5;
    f32 _A8;
};

}}}  // namespace scn::step::camera

#endif
