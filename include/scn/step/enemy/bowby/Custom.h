#ifndef SCN_STEP_ENEMY_BOWBY_CUSTOM_H
#define SCN_STEP_ENEMY_BOWBY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::bowby::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual void onCaptured();

    f32 playerAnger();
    bool isPlayerInArea();
    bool isAnimStart() const;
    void setAnimStart(bool start);

private:
    f32 mAngle;
    bool mIsAnimStart;
};

}
}
}
}

#endif
