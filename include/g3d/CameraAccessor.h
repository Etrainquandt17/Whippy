#ifndef G3D_CAMERAACCESSOR_H
#define G3D_CAMERAACCESSOR_H

#include "nw4r/g3d/g3d_camera.h"
#include "types.h"

namespace hel {
namespace math {
class Matrix34;
class Matrix44;
class Vector3;
}}  // namespace hel::math

namespace g3d {

class CameraAccessor : public nw4r::g3d::Camera {
public:
    CameraAccessor(const nw4r::g3d::Camera& camera) : nw4r::g3d::Camera(camera) {}

    hel::math::Matrix34 viewMtx() const;
    void setViewMtx(const hel::math::Matrix34& mtx) const;
    hel::math::Matrix44 projectionMtx() const;
    hel::math::Vector3 getPosition() const;
    void setPosition(const hel::math::Vector3& pos) const;
    nw4r::g3d::Camera::PostureInfo getPosture() const;
    void setPosture(const nw4r::g3d::Camera::PostureInfo& info) const;
    void setProjOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 zNear, f32 zFar) const;
    void setProjPerspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar) const;
    GXProjectionType getProjectionType() const;
    f32 getProjFovy() const;
    f32 getProjAspect() const;
    f32 getProjNear() const;
    f32 getProjFar() const;
    f32 getProjTop() const;
    f32 getProjBottom() const;
    f32 getProjLeft() const;
    f32 getProjRight() const;
};

}  // namespace g3d

#endif
