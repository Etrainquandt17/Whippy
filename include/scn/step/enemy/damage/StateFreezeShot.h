#ifndef SCN_STEP_ENEMY_DAMAGE_STATEFREEZESHOT_H
#define SCN_STEP_ENEMY_DAMAGE_STATEFREEZESHOT_H

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

class StateFreezeShot : public StateBase {
public:
    StateFreezeShot(Enemy* enemy, const u64& ownerUid);
    virtual ~StateFreezeShot();
    virtual void procAnim();
    virtual void procMove();
    virtual void procConstraint();
    virtual void procFixPos();

    void createWeapon(const util::ObjRefHandle<hero::Hero>& hero);

private:
    u32 mFrame;
    f32 mRot;
    u64 mOwnerUid;
    util::ObjRefHandle<weapon::Weapon> mWeapon;
};

}}}}  // namespace scn::step::enemy::damage

#endif
