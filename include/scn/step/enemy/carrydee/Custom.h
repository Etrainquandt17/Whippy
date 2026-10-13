#ifndef SCN_STEP_ENEMY_CARRYDEE_CUSTOM_H
#define SCN_STEP_ENEMY_CARRYDEE_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    bool isHaveKey();
    void fixPosKey();
    void onCarryStart();

private:
    // TODO: members.
    u32 _8[27];
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::carrydee::Custom>();

}
}

#endif
