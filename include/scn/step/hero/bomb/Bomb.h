#ifndef SCN_STEP_HERO_BOMB_BOMB_H
#define SCN_STEP_HERO_BOMB_BOMB_H

#include "hel/common/FixedString.h"
#include "scn/step/hero/AbilityBase.h"
#include "scn/step/hero/bomb/GearBombController.h"

namespace scn {
namespace step {
namespace hero {
namespace bomb {

class Bomb : public AbilityBase {
public:
    Bomb(Component& component, Hero& hero);
    virtual ~Bomb();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual void procAnim();
    virtual void onStateEndCleanUp();
    virtual void onGetEventItem();
    virtual void onGimmickReactChangeState();
    virtual void onStartClearDanceExternal();
    virtual void onEnterWarpLowper();
    virtual void onShowHero();
    virtual void onHideHero();
    virtual void onDead();
    virtual void onCaptured();
    virtual void onVacuumed();
    virtual void onStartDemo();
    virtual void onEnterDoor();

private:
    void dropBombIfHave();
    void clearBombIfHave();

    bool _C;
    GearBombController mGearBombController;
    f32 _40;
    u32 _44;
    hel::common::FixedString<40> _48;
    u32 _70[(0x124 - 0x70) / 4];
};

}
}
}
}

#endif
