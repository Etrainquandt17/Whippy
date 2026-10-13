#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/needleshot/StateStickEnemy.h"

#include "hel/math/Math.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/weapon/Param.h"
#include "scn/step/weapon/Weapon.h"
#include "scn/step/weapon/needleshot/Param.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

StateStickEnemy::StateStickEnemy(Weapon* weapon, const util::ObjRefHandle<enemy::Enemy>& enemy)
    : StateBase(weapon), mAlgorithm(*weapon, enemy), mFrame(0) {
    if (enemy.isAlive()) {
        hel::math::Vector3 offset;
        offset = obj().location().pos() - static_cast<const enemy::Enemy*>(enemy.operator->())->location().pos();
        f32 rot = obj().model().rotCtrl().getRotV();
        f32 length = obj().param().needleShot()._4;
        offset.x += length * hel::math::Math::CosDegF(rot);
        offset.y += length * hel::math::Math::SinDegF(rot);
        mAlgorithm.setOffset(offset);
    }
}

StateStickEnemy::~StateStickEnemy() {}

void StateStickEnemy::procAnim() {
    mFrame++;
    if (mFrame > obj().param().needleShot()._8) {
        obj().dead();
    } else if (!mAlgorithm.procAnim()) {
        return;
    }
}

void StateStickEnemy::procMove() {
    mAlgorithm.procMove();
}

void StateStickEnemy::procConstraint() {
    mAlgorithm.procConstraint();
}

}}}}  // namespace scn::step::weapon::needleshot
