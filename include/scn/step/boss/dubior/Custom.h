#ifndef SCN_STEP_BOSS_DUBIOR_CUSTOM_H
#define SCN_STEP_BOSS_DUBIOR_CUSTOM_H

#include "mcoll/detail/DetectResult.h"
#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/dubior/EnemyCtrl.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::dubior::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace dubior {

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
    virtual hel::math::Vector2 getFirstOffs() const;

    void setBodyCollDefault();
    void setBodyCollFastMove();
    void setBodyCollDash();
    void reqThunderGroundEffect();
    mcoll::detail::DetectResult detect(const hel::math::Vector2& pos, const hel::math::Vector2& move);
    EnemyCtrl& enemyCtrl();

private:
    EnemyCtrl mEnemyCtrl;
};

}
}
}
}

#endif
