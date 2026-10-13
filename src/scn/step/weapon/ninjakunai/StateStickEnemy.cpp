#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/ninjakunai/StateStickEnemy.h"

#include "gobj/Target.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/ninjakunai/Param.h"
#include "scn/step/weapon/ninjakunai/Utility.h"

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

StateStickEnemy::StateStickEnemy(Weapon* weapon, const util::ObjRefHandle<enemy::Enemy>& enemy)
    : StateBase(weapon), mAlgorithm(*weapon, enemy), mFrame(0) {
    if (enemy.isAlive()) {
        hel::math::Vector3 offset;
        offset = obj().location().pos() - static_cast<const enemy::Enemy*>(enemy.operator->())->location().pos();
        f32 length = obj().param().ninjaKunai()._0;
        f32 sign = obj().target().getSign();
        offset.x += sign * length;
        mAlgorithm.setOffset(offset);
    }
}

StateStickEnemy::~StateStickEnemy() {}

void StateStickEnemy::procAnim() {
    mFrame++;
    if (mFrame > obj().param().ninjaKunai()._4) {
        obj().dead();
    } else if (!mAlgorithm.procAnim()) {
        Utility::Rotate(obj());
    }
}

void StateStickEnemy::procMove() {
    mAlgorithm.procMove();
}

void StateStickEnemy::procConstraint() {
    mAlgorithm.procConstraint();
}

}}}}  // namespace scn::step::weapon::ninjakunai
