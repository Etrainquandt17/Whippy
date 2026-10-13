#ifndef SCN_STEP_WEAPON_ICUSTOM_H
#define SCN_STEP_WEAPON_ICUSTOM_H

#include "hel/common/RuntimeTypeInfo.h"

namespace scn {
namespace step {
namespace weapon {

class ICustom {
public:
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const = 0;
    virtual ~ICustom();
    virtual bool onInit() = 0;
    virtual void onDead() = 0;
    virtual void reqCustomDeadEffect() = 0;
};

}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::weapon::ICustom>();

}
}

#endif
