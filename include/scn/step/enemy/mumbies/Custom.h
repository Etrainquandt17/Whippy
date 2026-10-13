#ifndef SCN_STEP_ENEMY_MUMBIES_CUSTOM_H
#define SCN_STEP_ENEMY_MUMBIES_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::mumbies::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onHitPointIsZero();
    virtual bool onVacuumResist();
    virtual bool onDamaged();
    virtual bool onInWater();
    virtual bool onRecover();
    virtual void onCaptured();

    void setEndureFlag(bool endureFlag);

private:
    bool mEndureFlag;
    bool mIsDead;
};

}
}
}
}

#endif
