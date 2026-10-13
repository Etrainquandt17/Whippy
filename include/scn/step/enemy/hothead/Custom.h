#ifndef SCN_STEP_ENEMY_HOTHEAD_CUSTOM_H
#define SCN_STEP_ENEMY_HOTHEAD_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::hothead::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onInit();
    virtual bool onHitPointIsZero();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual void onCaptured();
    virtual void setupSuperEnemyEffect();

    bool isPlayerPosNear();
    bool isInViewRect();
    int setAfterAttackFrame();
};

}
}
}
}

#endif
