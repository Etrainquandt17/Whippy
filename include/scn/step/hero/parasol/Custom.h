#ifndef SCN_STEP_HERO_PARASOL_CUSTOM_H
#define SCN_STEP_HERO_PARASOL_CUSTOM_H

#include "ocoll/Attack.h"
#include "scn/step/hero/AbilityCustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace parasol {
class Custom;
}
}
}
}

namespace hel {
namespace common {
// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::hero::parasol::Custom>();
}
}

namespace scn {
namespace step {
namespace hero {
namespace parasol {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    ::ocoll::Attack& barrier();

private:
    ::ocoll::Attack mBarrier;
};

}
}
}
}

#endif
