#ifndef SCN_STEP_ENEMY_ICUSTOM_H
#define SCN_STEP_ENEMY_ICUSTOM_H

#include "hel/common/RuntimeTypeInfo.h"

namespace scn {
namespace step {
namespace enemy {

class ICustom {
public:
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const = 0;
    virtual ~ICustom();
    virtual bool onInit() = 0;
    virtual bool onHitPointIsZero() = 0;
    virtual bool onVacuumReceive() = 0;
    virtual bool onVacuumResist() = 0;
    virtual bool onDamaged() = 0;
    virtual bool onInWater() = 0;
    virtual bool onOutWater() = 0;
    virtual bool onRecover() = 0;
    virtual void onCaptured() = 0;
    virtual void onDead() = 0;
    virtual void onProcFixPos() = 0;
    virtual bool reqCustomDeadEffect() = 0;
    virtual void setupSuperEnemyEffect() = 0;
};

}
}
}

#endif
