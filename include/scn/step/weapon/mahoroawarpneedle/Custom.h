#ifndef SCN_STEP_WEAPON_MAHOROAWARPNEEDLE_CUSTOM_H
#define SCN_STEP_WEAPON_MAHOROAWARPNEEDLE_CUSTOM_H

#include "hel/common/RuntimeTypeInfo.h"
#include "scn/step/weapon/CustomBase.h"
#include "scn/step/weapon/Weapon.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarpneedle {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::mahoroawarpneedle::Custom>();

}
}

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarpneedle {

// TODO: the unit is not written yet; the members are read from its constructor.
class Custom : public CustomBase {
public:
    Custom(Weapon& weapon);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();

    void reqChangeStateStart();
    void reqChild();
    bool isChildDead();

private:
    bool mIsChildRequested;
    util::ObjRefHandle<Weapon> mChild;
};

}
}
}
}

#endif
