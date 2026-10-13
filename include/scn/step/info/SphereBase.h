#ifndef SCN_STEP_INFO_SPHEREBASE_H
#define SCN_STEP_INFO_SPHEREBASE_H

#include "scn/step/StageKind.h"
#include "types.h"

namespace hel {
namespace math {
class Vector3;
}
}

namespace lyt {
class PaneAccessor;
}

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {

class Component;

namespace info {

class SphereBase {
public:
    SphereBase(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, Component& component, bool, bool);

    void updateFrame();
    void updateSphereStateForLvMap(StageKind stage);
    void updateSphereStateForGetDemo(StageKind stage);
    f32 width();
    f32 baseWidth();
    void setOffset(const hel::math::Vector3& offset);
    void setVisibility(bool visible);
    void startGetAnim(u32 index);

private:
    u32 _0[0x1B8 / 4];
};

}
}
}

#endif
