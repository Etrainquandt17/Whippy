#ifndef SCN_STEP_GIMMICK_SPHERECOUNT_SPHERECOUNT_H
#define SCN_STEP_GIMMICK_SPHERECOUNT_SPHERECOUNT_H

#include "types.h"

namespace g3d {
class Root;
}

namespace hel {
namespace math {
class Vector3;
}}  // namespace hel::math

namespace scn {
namespace step {

class Component;

namespace gimmick {
namespace spherecount {

class SphereCount {
public:
    SphereCount(Component& component, const hel::math::Vector3& pos, u32 count);
    ~SphereCount();

    void registerToRoot(g3d::Root& root);

private:
    u32 _0[0x30 / 4];
};

}}}}  // namespace scn::step::gimmick::spherecount

#endif
