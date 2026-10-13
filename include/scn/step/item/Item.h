#ifndef SCN_STEP_ITEM_ITEM_H
#define SCN_STEP_ITEM_ITEM_H

#include "gobj/Location.h"
#include "hel/math/Vector3.h"
#include "scn/step/item/IState.h"
#include "scn/step/map/BinItemKind.h"
#include "types.h"
#include "util/StateChanger.h"

namespace gobj {
class FootState;
class Move;
}

namespace scn {
namespace step {

class Component;

namespace chara {

class Culling;
class Effect;
class LandConstraint;
class Lifetime;
class Model;
class Shadow;
class SoundSE;
class Water;

}
namespace ogen {
class Generator;
}
namespace item {

class Catcher;
class MapColl;
class ObjStop;
class Param;
class RotAnim;
class VacuumReceiver;

// TODO: members and the other functions.
class Item {
public:
    map::BinItemKind kind() const;
    u32 subKind() const;
    void setVisibility(bool isVisible);
    gobj::Location& location();
    chara::Model& model();
    chara::Effect& effectBack();
    util::StateChanger<IState, 256>& stateChanger();

    void dead();
    void deadWithEffect();
    void deadIgnoreObject(const hel::math::Vector2& pos);
    void deleteObjGenerator();
    void onCatched();
    bool isStageItem() const;
    bool isRequireRotAnim() const;
    bool isEventItem() const;
    bool isAbilityItem() const;
    f32 getRadius() const;
    u32 getVacuumedFrame() const;
    hel::math::Vector2 centerOffs() const;
    bool canCatch() const;
    void setCanCatch(bool canCatch);
    bool canGather() const;
    void setCanGather(bool canGather);
    void setGotIt(const hel::math::Vector2& pos, u32);
    void setAbilitySeatEmpty();
    void setGather(Catcher& catcher);
    void setRenderFore();
    bool isIgnoreCatchFrameZero() const;
    bool isDead() const;
    bool isVisible() const;
    u32 variation() const;
    hel::math::Vector2 initPos() const;
    u32 itemUID() const;
    ogen::Generator* objGenerator();

    Component& comp();
    const Param& param() const;
    gobj::FootState& footState();
    gobj::Move& move();
    chara::Effect& effect();
    chara::Effect& effectFore();
    chara::SoundSE& soundSE();
    ObjStop& objStop();
    chara::LandConstraint& landConstraint();
    MapColl& mapColl();
    VacuumReceiver& vacuumReceiver();
    chara::Culling& culling();
    chara::Lifetime& lifetime();
    chara::Shadow& shadow();
    RotAnim& rotAnim();
    chara::Water& water();
};

}}}  // namespace scn::step::item

#endif
