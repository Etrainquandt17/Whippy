#ifndef SCN_STEP_ENEMY_DAMAGE_STATEFREEZE_H
#define SCN_STEP_ENEMY_DAMAGE_STATEFREEZE_H

#include "hel/math/Vector3.h"
#include "scn/step/enemy/StateBase.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace hero {

class Hero;

}

namespace weapon {

class Weapon;

}

namespace enemy {

class Enemy;

namespace damage {

class StateFreeze : public StateBase {
public:
    StateFreeze(Enemy* enemy, u64 ownerUid);
    virtual ~StateFreeze();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();
    virtual void procObjCollReact();

    void createWeapon(const util::ObjRefHandle<hero::Hero>& hero);

private:
    u32 mFrame;
    util::ObjRefHandle<weapon::Weapon> mWeapon;
    hel::math::Vector3 mPos;
};

}}}}  // namespace scn::step::enemy::damage

#endif
