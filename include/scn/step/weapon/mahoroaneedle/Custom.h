#ifndef SCN_STEP_WEAPON_MAHOROANEEDLE_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROANEEDLE_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroaneedle::Custom>();

}
}

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

// TODO: stub
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);

private:
    u32 _8[4];
};

}
}
}
}

#endif
