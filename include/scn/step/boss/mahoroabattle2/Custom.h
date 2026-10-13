#ifndef SCN_STEP_BOSS_MAHOROABATTLE2_CUSTOM_H
#define SCN_STEP_BOSS_MAHOROABATTLE2_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::mahoroabattle2::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

class EnemyCtrl;
class KeptAbilityCtrl;
class LaserCtrl;
class MagicBallCtrl;
class NeedleCtrl;
class ScriptData;
class SuperSwordCtrl;

// TODO: members.
class Custom : public CustomBase {
public:
    Custom(Boss& boss);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~Custom();

    MagicBallCtrl& magicBallCtrl();
    NeedleCtrl& needleCtrl();
    EnemyCtrl& enemyCtrl();
    KeptAbilityCtrl& keptAbilityCtrl();
    LaserCtrl& laserCtrl();
    ScriptData& scriptData();
    SuperSwordCtrl& superSwordCtrl();

private:
    // TODO: members.
    u32 _8[429];
};

}
}
}
}

#endif
