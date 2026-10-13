#ifndef SCN_STEP_BOSS_LOWPER_CUSTOM_H
#define SCN_STEP_BOSS_LOWPER_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/lowper/BackEffectCtrl.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/EnemyCtrl.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace lowper {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::lowper::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace lowper {

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
    virtual void onProcMove();
    virtual void onProcFixPos();

    CollisionCtrl& collisionCtrl();
    DataBuff& dataBuff();
    EnemyCtrl& enemyCtrl();
    GearCtrl& gearCtrl();
    ItemCtrl& itemCtrl();
    WaftMoveCtrl& waftMoveCtrl();
    MiniBlackHoleCtrl& miniBlackHoleCtrl();

private:
    CollisionCtrl mCollisionCtrl;
    DataBuff mDataBuff;
    EnemyCtrl mEnemyCtrl;
    GearCtrl mGearCtrl;
    ItemCtrl mItemCtrl;
    WaftMoveCtrl mWaftMoveCtrl;
    MiniBlackHoleCtrl mMiniBlackHoleCtrl;
    BackEffectCtrl mBackEffectCtrl;
};

}
}
}
}

#endif
