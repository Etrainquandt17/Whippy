#ifndef SCN_STEP_ENEMY_LARPA_CUSTOM_H
#define SCN_STEP_ENEMY_LARPA_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace larpa {

// TODO: members and the other functions.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    void setBodyColl();
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::larpa::Custom>();

}
}

#endif
