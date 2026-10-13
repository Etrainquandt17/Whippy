#ifndef SCN_STEP_HERO_ABILITYMANAGER_H
#define SCN_STEP_HERO_ABILITYMANAGER_H

#include "mem/ExplicitScopedPtr.h"
#include "scn/step/hero/AbilityBase.h"
#include "scn/step/hero/AbilityCustomBase.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/sfx/DarknessLightSizeKind.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace hero {

class Hero;
namespace superice {
class Custom;
}
namespace needle {
class Custom;
}
namespace supersword {
class Custom;
}
namespace spark {
class Custom;
}
namespace ninja {
class Custom;
}
namespace fighter {
class Custom;
}
namespace spear {
class Custom;
}
namespace dee {
class Custom;
}

class AbilityManager {
public:
    bool chkDiscardAbility();
    void onGimmickReactChangeState();
    bool tryToChangeState();
    void initAbility(int kind);
    void startAbilitySilent();
    bool tryToChangeStateOnDamage();
    void setFuel(u32 fuel);
    bool isSuper() const;
    bool isSuperActionTime() const;
    void superStopRelease();
    bool haveAbility() const;
    bool isStarted() const;
    AbilityKind abilityKind() const;
    void changeAbilityIfPossible();
    void dropAbility();
    void clearAbility();
    bool isForbidGuard() const;
    bool isReservedChange() const;
    void discardAbility(bool);
    void setActionInterval(u32 interval);
    u32 getFuel() const;
    void lockFuel();
    void unlockFuel();
    u32 getUseCount() const;
    void incUseCount();
    void initFuel(u32 fuel);
    void decFuel(u32 fuel);
    void onSuperActionStart();
    void onSuperActionEnd();
    supersword::Custom& customSuperSword();
    superice::Custom& customSuperIce();
    needle::Custom& customNeedle();
    void setCustomDarknessLightSizeKind(sfx::DarknessLightSizeKind kind);
    void resetCustomDarknessLightSizeKind();
    u32 getChainPhase() const;
    void setChainPhase(u32 phase);
    void setChainRespite(u32 respite);
    spark::Custom& customSpark();
    bool isFixedAbility() const;
    ninja::Custom& customNinja();
    fighter::Custom& customFighter();
    spear::Custom& customSpear();
    dee::Custom& customDee();

private:
    void initAbilityCore(int kind);
    void clearAbilityCore(bool);
    void reserveChangeAbility(int kind, bool);
    void startAbilityCore(bool);

    Hero& mHero;
    Component& mComponent;
    mem::ExplicitScopedPtr<AbilityBase> mAbility;
    mem::ExplicitScopedPtr<AbilityCustomBase> mCustom;
    int mKind;
    bool _1C;
    u8 _1D[0x28 - 0x1D];
    u32 mFuel;
    u32 mFuelMax;
    u8 _30[0x1C];
    bool _4C;
};

}}}  // namespace scn::step::hero

#endif
