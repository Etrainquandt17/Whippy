#ifndef SCN_STEP_ENEMY_KABU_CUSTOM_H
#define SCN_STEP_ENEMY_KABU_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInWater();

    int setJumpWaitTime();
    void setIsInvisible(bool isInvisible);

private:
    bool mIsInvisible;
};

}
}
}
}

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::kabu::Custom>();

}
}

#endif
