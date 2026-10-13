#ifndef SCN_STEP_BOSS_METALGENERAL_CUSTOM_H
#define SCN_STEP_BOSS_METALGENERAL_CUSTOM_H

#include "scn/step/boss/CustomBase.h"
#include "scn/step/boss/metalgeneral/CollisionCtrl.h"
#include "scn/step/boss/metalgeneral/DamageInfoCtrl.h"
#include "scn/step/boss/metalgeneral/WeaponCtrl.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

class Custom;

}
}
}
}

namespace hel {
namespace common {

// TODO: an instance of the general template, which hel/common/RuntimeTypeInfo.h cannot define yet.
template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::boss::metalgeneral::Custom>();

}
}

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

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

    void setupGear();
    CollisionCtrl& collisionCtrl();
    WeaponCtrl& weaponCtrl();

private:
    CollisionCtrl mCollisionCtrl;
    WeaponCtrl mWeaponCtrl;
    DamageInfoCtrl mDamageInfoCtrl;
};

}
}
}
}

#endif
