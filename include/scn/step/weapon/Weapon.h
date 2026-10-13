#ifndef SCN_STEP_WEAPON_WEAPON_H
#define SCN_STEP_WEAPON_WEAPON_H

#include "hel/math/Vector2.h"
#include "scn/step/weapon/IState.h"
#include "scn/step/weapon/Kind.h"
#include "types.h"
#include "util/StateChanger.h"

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

namespace chara {
class Culling;
class GroundChecker;
class HitStop;
class LandConstraint;
class Location;
class Model;
class ObjCollLite;
class Shadow;
class Water;
class WorldCage;
}
}
}

namespace scn {
namespace step {
namespace weapon {

class CameraTarget;
class DarknessLight;
class Effect;
class Flash;
class ICustom;
class MapColl;
class ObjCollReact;
class ObjStop;
class Param;
class SuperStop;

// TODO: members.
class Weapon {
public:
    chara::Model& model();
    chara::Location& location() const;
    Effect& effect();
    void dead();
    ICustom* custom();
    gobj::Target& target();

    Component& comp();
    util::StateChanger<IState, 256>& stateChanger();
    gobj::Move& move();
    MapColl& mapColl();
    const Param& param() const;
    chara::ObjCollLite& objColl();
    ObjCollReact& objCollReact();
    ObjStop& objStop();
    SuperStop& superStop();
    chara::HitStop& hitStop();
    chara::LandConstraint& landConstraint();
    snd::SERequestor& soundSE();
    Flash& flash();
    gobj::FootState& footState();
    chara::Shadow& shadow();
    chara::Culling& culling();
    chara::Water& water();
    chara::WorldCage& worldCage();
    chara::GroundChecker& groundChecker();
    CameraTarget& cameraTarget();
    DarknessLight& darknessLight();
    Kind kind() const;
    u32 variation() const;
    hel::math::Vector2 targetPos() const;
    bool isDead() const;
    bool isVisible() const;
    bool isValidAttackRumble() const;
    void deadWithEffect();
    void setVisibility(bool isVisible);
    void setValidAttackRumble(bool isValid);
    void setDarknessLightVisibility(bool isVisible);
};

}
}
}

#endif
