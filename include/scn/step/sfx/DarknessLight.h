#ifndef SCN_STEP_SFX_DARKNESSLIGHT_H
#define SCN_STEP_SFX_DARKNESSLIGHT_H

#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "types.h"
#ifdef SCN_STEP_SFX_DARKNESSLIGHT_MEMBERS
#include "g3d/StdModel.h"
#include "mem/ExplicitScopedPtr.h"
#endif

namespace hel {
namespace math {
class Vector3;
}
}

namespace scn {
namespace step {

class Component;

namespace sfx {

// TODO: members and the other functions. The destructor is implicit: a unit that holds one by value defines
// SCN_STEP_SFX_DARKNESSLIGHT_MEMBERS ahead of its includes and gets the size (0x38) and the two models.
class DarknessLight {
public:
    DarknessLight(Component& component, bool, DarknessLightSizeKind sizeKind);

    void setCustomScale(f32 scale);
    void setPos(const hel::math::Vector3& pos);
#ifdef SCN_STEP_SFX_DARKNESSLIGHT_MEMBERS

private:
    u32 _0[0x28 / 4];
    mem::ExplicitScopedPtr<g3d::StdModel> _28;
    mem::ExplicitScopedPtr<g3d::StdModel> _30;
#endif
};

}
}
}

#endif
