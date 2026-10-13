#include "g3d/CameraAccessor.h"

#include "hel/math/Matrix34.h"
#include "hel/math/Matrix44.h"
#include "hel/math/Vector3.h"

namespace g3d {

hel::math::Matrix34 CameraAccessor::viewMtx() const {
    hel::math::Matrix34 mtx;
    GetCameraMtx(reinterpret_cast<nw4r::math::MTX34*>(&mtx));
    return mtx;
}

void CameraAccessor::setViewMtx(const hel::math::Matrix34& mtx) const {
    const_cast<CameraAccessor*>(this)->SetCameraMtxDirectly(reinterpret_cast<const nw4r::math::MTX34&>(mtx));
}

hel::math::Matrix44 CameraAccessor::projectionMtx() const {
    hel::math::Matrix44 mtx;
    GetProjectionMtx(&mtx.m);
    return mtx;
}

hel::math::Vector3 CameraAccessor::getPosition() const {
    nw4r::math::VEC3 pos;
    GetPosition(&pos);
    return hel::math::Vector3(pos);
}

void CameraAccessor::setPosition(const hel::math::Vector3& pos) const {
    if (&pos == 0) {
        return;
    }
    const_cast<CameraAccessor*>(this)->SetPosition(reinterpret_cast<const nw4r::math::VEC3&>(pos));
}

nw4r::g3d::Camera::PostureInfo CameraAccessor::getPosture() const {
    nw4r::g3d::Camera::PostureInfo info;
    GetPosture(&info);
    return info;
}

void CameraAccessor::setPosture(const nw4r::g3d::Camera::PostureInfo& info) const {
    const_cast<CameraAccessor*>(this)->SetPosture(info);
}

void CameraAccessor::setProjOrtho(f32 top, f32 bottom, f32 left, f32 right, f32 zNear, f32 zFar) const {
    const_cast<CameraAccessor*>(this)->SetOrtho(top, bottom, left, right, zNear, zFar);
}

void CameraAccessor::setProjPerspective(f32 fovy, f32 aspect, f32 zNear, f32 zFar) const {
    const_cast<CameraAccessor*>(this)->SetPerspective(fovy, aspect, zNear, zFar);
}

GXProjectionType CameraAccessor::getProjectionType() const {
    return GetProjectionType();
}

f32 CameraAccessor::getProjFovy() const {
    return const_cast<CameraAccessor*>(this)->ref().projFovy;
}

f32 CameraAccessor::getProjAspect() const {
    return const_cast<CameraAccessor*>(this)->ref().projAspect;
}

f32 CameraAccessor::getProjNear() const {
    return const_cast<CameraAccessor*>(this)->ref().projNear;
}

f32 CameraAccessor::getProjFar() const {
    return const_cast<CameraAccessor*>(this)->ref().projFar;
}

f32 CameraAccessor::getProjTop() const {
    return const_cast<CameraAccessor*>(this)->ref().projTop;
}

f32 CameraAccessor::getProjBottom() const {
    return const_cast<CameraAccessor*>(this)->ref().projBottom;
}

f32 CameraAccessor::getProjLeft() const {
    return const_cast<CameraAccessor*>(this)->ref().projLeft;
}

f32 CameraAccessor::getProjRight() const {
    return const_cast<CameraAccessor*>(this)->ref().projRight;
}

}  // namespace g3d
