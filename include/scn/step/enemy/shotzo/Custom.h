#ifndef SCN_STEP_ENEMY_SHOTZO_CUSTOM_H
#define SCN_STEP_ENEMY_SHOTZO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::shotzo::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace shotzo {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onInWater();

    f32 aimAngle() const;
    void setAimAngle(f32 angle);
    f32 playerAngle();
    bool isPlayerInAimArea();
    bool isFixPos() const;

private:
    f32 mAimAngle;
};

}
}
}
}

#endif
