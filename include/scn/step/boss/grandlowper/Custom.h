#ifndef SCN_STEP_BOSS_GRANDLOWPER_CUSTOM_H
#define SCN_STEP_BOSS_GRANDLOWPER_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace grandlowper {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::grandlowper::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace grandlowper {

class CoverCtrl;
class EnemyGenCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    EnemyGenCtrl& enemyGenCtrl();
    CoverCtrl& coverCtrl();

private:
    // TODO: members.
    u32 _8[184];
};

}
}
}
}

#endif
