#ifndef SCN_STEP_HERO_SUPERICE_CUSTOM_H
#define SCN_STEP_HERO_SUPERICE_CUSTOM_H

#include "scn/step/hero/AbilityCustomBase.h"
#include "scn/step/hero/superice/SnowBall.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace superice {
class Custom;
}
}
}
}

namespace hel {
namespace common {
// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::hero::superice::Custom>();
}
}

namespace scn {
namespace step {
namespace hero {
namespace superice {

class Custom : public AbilityCustomBase {
public:
    Custom(Hero& hero);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    SnowBall& snowBall();

private:
    SnowBall mSnowBall;
};

}
}
}
}

#endif
