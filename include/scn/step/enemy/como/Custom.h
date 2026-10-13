#ifndef SCN_STEP_ENEMY_COMO_CUSTOM_H
#define SCN_STEP_ENEMY_COMO_CUSTOM_H

#include "scn/step/enemy/CustomBase.h"
#include "scn/step/enemy/como/ThreadCtrl.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::como::Custom>();

}
}

namespace scn {
namespace step {
namespace enemy {
namespace como {

class Custom : public CustomBase {
public:
    Custom(Enemy& enemy);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();
    virtual bool onHitPointIsZero();
    virtual void onCaptured();
    virtual void onProcFixPos();

    ThreadCtrl& threadCtrl();

private:
    ThreadCtrl mThreadCtrl;
};

}
}
}
}

#endif
