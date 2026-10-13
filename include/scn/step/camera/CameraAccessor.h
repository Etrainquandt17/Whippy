#ifndef SCN_STEP_CAMERA_CAMERAACCESSOR_H
#define SCN_STEP_CAMERA_CAMERAACCESSOR_H

#include "hel/math/Vector2.h"
#include "scn/step/camera/Kind.h"

namespace hel {
namespace math {
class Matrix44;
class Vector3;
}}  // namespace hel::math

namespace scn {
namespace step {
namespace camera {

class CameraAccessor {
public:
    hel::math::Vector2 toLayoutPos(Kind kind, const hel::math::Vector3& pos) const;
    hel::math::Matrix44 projConvMtx(Kind kind) const;
    f32 projAspect(Kind kind) const;
};

}}}  // namespace scn::step::camera

#endif
