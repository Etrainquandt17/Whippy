#ifndef SCN_ARENA_CAMERA_H
#define SCN_ARENA_CAMERA_H

#include "hel/math/Vector3.h"
#include "types.h"

namespace scn {
namespace arena {

// TODO: the size is not known.
class Camera {
public:
    Camera();

    void setPos(hel::math::Vector3 pos);
    void setTargetPos(hel::math::Vector3 pos);
    void setCameraAnimFlag(bool flag);

private:
    u32 _0[3];
    hel::math::Vector3 mTargetPos;
    u32 _18[2];
    bool mCameraAnimFlag;
};

}}  // namespace scn::arena

#endif
