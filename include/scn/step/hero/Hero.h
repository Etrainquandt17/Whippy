#ifndef SCN_STEP_HERO_HERO_H
#define SCN_STEP_HERO_HERO_H

#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "types.h"

namespace hid {
class RumbleRequestor;
}

namespace util {
class IState;
template <typename T, int N>
class StateChanger;
}

namespace gobj {
class Target;
class FootState;
class Move;
}

namespace scn {
namespace step {

class Component;

namespace chara {
class Location;
class GroundChecker;
class HitPoint;
class Knockback;
class HitStop;
class LandConstraint;
class WorldCage;
}

namespace carryitem {
class User;
}

namespace info {
class HeroPanel;
}

namespace vacuum {
class Attacker;
}

namespace hero {

class AbilityCrashCtrl;
class CaptureAttacker;
class ItemCatcher;
class InertialMove;
class CarryItemRide;
class IState;
class AdditionalMove;
class Dead;
class Flash;
class Hat;
class LogoutController;
class Nururi;
class ObjStop;
class VacuumReceiver;
class Stepping;
class RunChecker;
class CommandManager;
class Hang;
class Kiss;
class AbilityManager;
class CameraTarget;
class CaptureHeroReceiver;
class Guard;
class PowerCharge;
class Effect;
class GatherItem;
class Heap;
class Hid;
class Invincible;
class Model;
class ObjColl;
class SoundSE;
class Squash;
class StagingCtrl;
class StateChecker;
class Water;
class WearBack;
class InvisibleControl;
class MapColl;
class Param;
class Piggyback;
class Pinch;
class ShakeCharge;
class LandAttribute;
class Landing;
class ItemCollReact;
class ChargeFlash;
class DamageFlash;

class Hero {
public:
    void setCanReactGimmick(bool canReact);
    void setCanCatchItem(bool canCatch);
    void changeAbilityEnf(AbilityKind kind);
    AdditionalMove& additionalMove();
    Stepping& stepping();
    RunChecker& runChecker();
    CommandManager& commandManager();
    Hang& hang();
    Kiss& kiss();
    vacuum::Attacker& vacuumAttacker();
    AbilityManager& abilityManager();
    carryitem::User& carryItemUser();
    Component& comp();
    Heap& heap();
    Hid& hid() const;
    info::HeroPanel& infoHeroPanel();
    bool isVisible() const;
    Model& model();
    u32 padChan() const;
    SoundSE& soundSE();
    StateChecker& stateChecker();
    Water& water();
    WearBack& wearBack();
    GatherItem& gatherItem();
    hid::RumbleRequestor& hidRumble();
    Invincible& invincible();
    ObjColl& objColl();
    Squash& squash();
    StagingCtrl& stagingCtrl();
    Effect& effect();
    bool isMainPlayer() const;
    Kind kind() const;
    const chara::Location& location() const;
    gobj::Target& target();
    MapColl& mapColl();
    Pinch& pinch();
    ShakeCharge& shakeCharge();
    InvisibleControl& invisibleControl();
    Piggyback& piggyback();
    const Param& param() const;
    gobj::FootState& footState();
    chara::GroundChecker& groundChecker();
    CaptureHeroReceiver& captureHeroReceiver();
    // TODO: the size of the state buffer is a guess.
    util::StateChanger<IState, 256>& stateChanger();
    Guard& guard();
    PowerCharge& powerCharge();
    CameraTarget& cameraTarget();
    void setVisibility(bool isVisible);
    gobj::Move& move();
    chara::Location& location();
    DamageFlash& damageFlash();
    LogoutController& logoutController();
    chara::HitStop& hitStop();
    Dead& dead();
    Flash& flash();
    Nururi& nururi();
    chara::WorldCage& worldCage();
    VacuumReceiver& vacuumReceiver();
    Hat& hat();
    ObjStop& objStop();
    AbilityCrashCtrl& abilityCrashCtrl();
    ItemCatcher& itemCatcher();
    InertialMove& inertialMove();
    chara::LandConstraint& landConstraint();
    CarryItemRide& carryItemRide();
    LandAttribute& landAttribute();
    Landing& landing();
    ItemCollReact& itemCollReact();
    chara::Knockback& knockback();
    void setRenderFore(bool isFore);
    ChargeFlash& chargeFlash();
    chara::HitPoint& hitPoint();
    CaptureAttacker& captureAttacker();
};

}
}
}

#endif
