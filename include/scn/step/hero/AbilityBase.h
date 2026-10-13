#ifndef SCN_STEP_HERO_ABILITYBASE_H
#define SCN_STEP_HERO_ABILITYBASE_H

#include "types.h"

namespace scn {
namespace step {

class Component;

namespace hero {

class Hero;

class AbilityBase {
public:
    AbilityBase(Component& component, Hero& hero);
    virtual ~AbilityBase();
    virtual void setup();
    virtual bool tryToChangeStateOnCarry();
    virtual bool tryToChangeStateOnInterval();
    virtual bool tryToChangeStateOnDamage();
    virtual bool tryToChangeState();
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
    virtual void procAnim();
    virtual void procMove();
    virtual void procObjCollReact();
    virtual bool isDepleted() const;

protected:
    Component& mComponent;
    Hero& mHero;
};

}
}
}

#endif
