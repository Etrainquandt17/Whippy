#ifndef SCN_STEP_BOSS_BOSS_H
#define SCN_STEP_BOSS_BOSS_H

#include "scn/step/boss/IState.h"
#include "scn/step/map/BinBossKind.h"
#include "scn/step/map/BinBossVariation.h"
#include "util/StateChanger.h"

namespace gobj {

class FootState;
class Move;
class Target;

}

namespace hel {
namespace math {

class Vector2;

}}  // namespace hel::math

namespace mem {

class IAllocator;

}

namespace util {

template <typename T>
class ObjRefHandle;

}

namespace scn {
namespace step {

class Component;

namespace chara {

class HitPoint;
class HitStop;
class Location;
class Model;
class ObjColl;
class ScriptTrigger;
class Shadow;
class WorldCage;

}

namespace info {

class BossPanel;

}

namespace boss {

class Effect;
class Angry;
class BarrierInvincible;
class DamageInvincible;
class BGMCtrl;
class InfoHitPointCtrl;
class BrainCtrl;
class Flash;
class GearManager;
class Guard;
class Handicap;
class HateCtrl;
class ICustom;
class Invincible;
class MapColl;
class ObjStop;
class Param;
class SoundSE;
class StagingCtrl;
class StateCallback;
class SuperStop;
class VacuumReceiver;

class Boss {
public:
    util::ObjRefHandle<Boss> handle();
    Effect& effect();
    info::BossPanel& infoBossPanel();
    util::StateChanger<IState, 256>& stateChanger();
    SoundSE& soundSE();
    GearManager& gearManager();
    Flash& flash();
    Angry& angry();
    mem::IAllocator& allocator();
    chara::Location& location();
    StagingCtrl& stagingCtrl();
    hel::math::Vector2 basePos() const;
    hel::math::Vector2 camOffs() const;
    Component& comp();
    ICustom* custom();
    const Param& param() const;
    gobj::Target& target();
    gobj::FootState& footState();
    gobj::Move& move();
    chara::Model& model();
    chara::ScriptTrigger& scriptTrigger();
    chara::ObjColl& objColl();
    chara::HitPoint& hitPoint();
    chara::Shadow& shadow();
    chara::WorldCage& worldCage();
    BrainCtrl& brainCtrl();
    MapColl& mapColl();
    VacuumReceiver& vacuumReceiver();
    Guard& guard();
    HateCtrl& hateCtrl();
    Invincible& invincible();
    StateCallback& stateCallback();
    SuperStop& superStop();
    ObjStop& objStop();
    chara::HitStop& hitStop();
    u32 level() const;
    map::BinBossKind kind() const;
    bool isSuper() const;
    map::BinBossVariation variation() const;
    Handicap& handicap();
    BGMCtrl& bgmCtrl();
    InfoHitPointCtrl& infoHitPointCtrl();
    bool isDead() const;
    bool isGeneratorExist() const;
    void dead();
    BarrierInvincible& barrierInvincible();
    DamageInvincible& damageInvincible();
};

}}}  // namespace scn::step::boss

#endif
