#ifndef SCN_STEP_ENEMY_BULBY_CUSTOM_H
#define SCN_STEP_ENEMY_BULBY_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::bulby::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onDamaged();
    virtual void onCaptured();
    virtual void onProcFixPos();

    bool isBuried() const;
    void setIsBuried(bool isBuried);

private:
    bool mIsBuried;
    int mX;
    int mY;
};

}
}
}
}

#endif
