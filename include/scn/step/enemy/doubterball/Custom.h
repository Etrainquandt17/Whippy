#ifndef SCN_STEP_ENEMY_DOUBTERBALL_CUSTOM_H
#define SCN_STEP_ENEMY_DOUBTERBALL_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubterball {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::doubterball::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace doubterball {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onDamaged();
    virtual void onDead();
    virtual bool reqCustomDeadEffect();
};

}
}
}
}

#endif
