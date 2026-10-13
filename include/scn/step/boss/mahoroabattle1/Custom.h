#ifndef SCN_STEP_BOSS_MAHOROABATTLE1_CUSTOM_H
#define SCN_STEP_BOSS_MAHOROABATTLE1_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::mahoroabattle1::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

class BarrierCtrl;
class EnemyCtrl;
class MagicBallCtrl;
class NeedleCtrl;
class StormCtrl;
class WarpHoleCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    NeedleCtrl& needleCtrl();
    EnemyCtrl& enemyCtrl();
    MagicBallCtrl& magicBallCtrl();
    BarrierCtrl& barrierCtrl();
    StormCtrl& stormCtrl();
    WarpHoleCtrl& warpHoleCtrl();

private:
    // TODO: members.
    u32 _8[787];
};

}
}
}
}

#endif
