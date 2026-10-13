#ifndef SCN_STEP_ENEMY_SHELD_CUSTOM_H
#define SCN_STEP_ENEMY_SHELD_CUSTOM_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::sheld::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual bool onInit();
    virtual bool onVacuumReceive();
    virtual bool onDamaged();

    void resetPos();
    void setPos();
    bool isSetPos() const;
    void initEscape();
    bool isEscape() const;
    void resetNuru();
    void setNuru();
    bool isNuru() const;

private:
    int mEscapeState;
    hel::math::Vector2 mPos;
    bool mIsNuru;
};

}
}
}
}

#endif
