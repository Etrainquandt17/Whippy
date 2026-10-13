#ifndef SCN_STEP_WEAPON_ROAHOAR_CUSTOM_H
#define SCN_STEP_WEAPON_ROAHOAR_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::roahoar::Custom>();

}
}

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
};

}
}
}
}

#endif
