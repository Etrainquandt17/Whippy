#ifndef SCN_STEP_HERO_SUPERSWORD_CUSTOM_H
#define SCN_STEP_HERO_SUPERSWORD_CUSTOM_H

#include "scn/step/hero/AbilityCustomBase.h"
#include "scn/step/hero/supersword/SwordSelector.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace supersword {
class Custom;
}
}
}
}

namespace hel {
namespace common {
// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::hero::supersword::Custom>();
}
}

namespace scn {
namespace step {
namespace hero {
namespace supersword {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    SwordSelector& swordSelector();

private:
    SwordSelector mSwordSelector;
};

}
}
}
}

#endif
