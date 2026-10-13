#ifndef SCN_STEP_WEAPON_CUSTOMBASE_H
#define SCN_STEP_WEAPON_CUSTOMBASE_H

#include "hel/common/NonCopyable.h"
#include "scn/step/weapon/ICustom.h"

namespace scn {
namespace step {
namespace weapon {

class CustomBase;
class Weapon;

}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::CustomBase>();

}
}

namespace scn {
namespace step {
namespace weapon {

class CustomBase : public ICustom, private hel::common::NonCopyable {
public:
    CustomBase(Weapon& weapon);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual void onDead();
    virtual void reqCustomDeadEffect();

    Weapon& obj() const;
    Weapon& obj();

private:
    Weapon& mObj;
};

}
}
}

#endif
