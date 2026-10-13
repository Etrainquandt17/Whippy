#ifndef SCN_STEP_WEAPON_GOLIATHENERGYBALL_CUSTOM_H
#define SCN_STEP_WEAPON_GOLIATHENERGYBALL_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::goliathenergyball::Custom>();

}
}

namespace scn {
namespace step {
namespace weapon {
namespace goliathenergyball {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void setScaleUpFrame(u32 frame);
    u32 getScaleUpFrame() const;

private:
    u32 mScaleUpFrame;
};

}
}
}
}

#endif
