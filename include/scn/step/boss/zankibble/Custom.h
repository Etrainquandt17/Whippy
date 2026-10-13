#ifndef SCN_STEP_BOSS_ZANKIBBLE_CUSTOM_H
#define SCN_STEP_BOSS_ZANKIBBLE_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/zankibble/EnemyCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::zankibble::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

class Custom : public CustomBase {
public:
    Custom(Boss& boss);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual void onInit();
    virtual void onAppear();
    virtual void onStart();
    virtual void onDamage();
    virtual void onDead();
    virtual void onProcAnim();
    virtual void onProcFixPos();

    EnemyCtrl& enemyCtrl();

private:
    EnemyCtrl mEnemyCtrl;
};

}
}
}
}

#endif
