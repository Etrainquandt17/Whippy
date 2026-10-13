#ifndef SCN_STEP_SPHEREUNLOCKKIND_H
#define SCN_STEP_SPHEREUNLOCKKIND_H

namespace scn {
namespace step {

// TODO: name the kinds. 0xFF is what the challenge kinds without a challenge map to.
enum SphereUnlockKind {
    SPHERE_UNLOCK_KIND_0,
    SPHERE_UNLOCK_KIND_1,
    SPHERE_UNLOCK_KIND_2,
    SPHERE_UNLOCK_KIND_3,
    SPHERE_UNLOCK_KIND_4,
    SPHERE_UNLOCK_KIND_5,
    SPHERE_UNLOCK_KIND_6,
    SPHERE_UNLOCK_KIND_NONE = 0xFF,
};

}}  // namespace scn::step

#endif
