#ifndef SCN_STEP_HERO_SLEEP_STATESLEEPSLEEP_H
#define SCN_STEP_HERO_SLEEP_STATESLEEPSLEEP_H

#include "scn/step/hero/StateBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace hero {

}
namespace weapon {
class Weapon;
}
namespace hero {
namespace sleep {

class StateSleepSleep : public StateBase {
public:
    StateSleepSleep(Hero* hero);
    virtual ~StateSleepSleep();
    virtual void procAnim();
    virtual void procMove();
    virtual void procFixPos();

private:
    void clearAbility();
    void procAnimNormal();
    void procAnimSnotBubble();
    void procAnimWaitShrink();
    void procAnimWakeUp();
    void changeSubStateSnotBubble();
    void changeSubStateWaitShrink();
    void wakeUp();
    void wakeUpWithBubbleBurst();
    void decideWeaponScale();
    f32 shakeScale();
    void updateWeapon(f32 scale);
    void createWeapon();
    bool isStartSnotBubble();
    void chkWakeUp();
    void initShakeCharge();

    u32 mFrame;
    f32 mShakeAngle;
    f32 mShrinkSpeed;
    f32 mScale;
    int mSubState;
    util::ObjRefHandle<weapon::Weapon> mWeapon;
};

}
}
}
}

#endif
