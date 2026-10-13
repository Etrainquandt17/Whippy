#ifndef SCN_STEP_ENEMY_ENEMY_H
#define SCN_STEP_ENEMY_ENEMY_H

#include "hel/math/Vector2.h"
#include "scn/step/enemy/IState.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/map/BinEnemyDirType.h"
#include "scn/step/map/BinEnemyKind.h"
#include "scn/step/map/BinEnemySize.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "util/StateChanger.h"

namespace util {

template <typename T>
class ObjRefHandle;

}

namespace gobj {

class FootState;
class Move;
class Target;

}

namespace snd {

class SERequestor;

}

namespace scn {
namespace step {

class Component;

namespace ogen {

class Generator;

}

namespace chara {

class CliffChecker;
class Culling;
class GroundChecker;
class DamageInfo;
class HitPoint;
class HitStop;
class Location;
class Model;
class ObjColl;
class Water;
class WorldCage;

}

namespace enemy {

class BrainCtrl;
class CaptureReceiver;
struct CharaParam;
class DamageFlash;
class Effect;
class Flash;
class ICustom;
class InterruptStateChanger;
class MapColl;
class Nururi;
class ObjCollReact;
class ObjStop;
class Param;
class Shadow;
class Signal;
class StateChecker;
class VacuumReceiver;

// TODO: members.
class Enemy {
public:
    util::StateChanger<IState, 256>& stateChanger();
    ICustom* custom();
    MapColl& mapColl();
    gobj::Move& move();
    const Param& param() const;
    Effect& effect();
    snd::SERequestor& soundSE();
    snd::SERequestor& soundSEState();
    Flash& flash();
    u32 level() const;
    gobj::Target& target();
    chara::Model& model();
    chara::ObjColl& objColl();
    Component& comp();
    const Component& comp() const;
    ObjStop& objStop();
    const chara::Location& location() const;
    chara::Location& location();
    gobj::FootState& footState();
    BrainCtrl& brainCtrl();
    chara::CliffChecker& cliffChecker();
    chara::GroundChecker& groundChecker();
    Nururi& nururi();
    Shadow& shadow();
    VacuumReceiver& vacuumReceiver();
    Signal& signal();
    chara::HitPoint& hitPoint();
    void dead();
    void deadIndependent();
    void deadWithEffect();
    void deadWithEffectNoItem();
    void deadChallenge();
    map::BinEnemyDirType dirType() const;
    ObjCollReact& objCollReact();
    map::BinEnemyKind kind() const;
    util::ObjRefHandle<Enemy> handle();
    const CharaParam& charaParam() const;
    map::BinEnemyVariation variation() const;
    map::BinEnemySize size() const;
    void setPotentialCount(u32 count);
    void setVacuumedCount(u32 count);
    void setAbilityKind(hero::AbilityKind kind);
    ogen::Generator* objGenerator();
    void setObjGenerator(ogen::Generator& generator);
    void deleteObjGenerator();
    chara::Culling& culling();
    chara::Water& water();
    CaptureReceiver& captureReceiver();
    bool isSuper() const;
    chara::WorldCage& worldCage();
    chara::DamageInfo& damageInfo();
    DamageFlash& damageFlash();
    void recover();
    chara::HitStop& hitStop();
    StateChecker& stateChecker();
    InterruptStateChanger& interruptStateChanger();
    hel::math::Vector2 getBasePos() const;
};

}}}  // namespace scn::step::enemy

#endif
