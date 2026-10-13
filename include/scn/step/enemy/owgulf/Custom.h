#ifndef SCN_STEP_ENEMY_OWGULF_CUSTOM_H
#define SCN_STEP_ENEMY_OWGULF_CUSTOM_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/CustomBase.h"
#include "scn/step/weapon/owgulffeather/VariationKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::owgulf::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    void shot(hel::math::Vector3 pos, hel::math::Vector3 velocity, weapon::owgulffeather::VariationKind kind);
};

}
}
}
}

#endif
