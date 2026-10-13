#ifndef SCN_STEP_WEAPON_GRANDLOWPERHOLE_CUSTOM_H
#define SCN_STEP_WEAPON_GRANDLOWPERHOLE_CUSTOM_H

#include "scn/step/weapon/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {
namespace grandlowperhole {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::grandlowperhole::Custom>();

}
}

namespace scn {
namespace step {
namespace weapon {
namespace grandlowperhole {

class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void stop();
    void move();
    bool isMove() const;

private:
    bool mIsMove;
};

}
}
}
}

#endif
