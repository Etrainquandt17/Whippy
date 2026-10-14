#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#define NW4R_UT_LINKLIST_GETNODEFROMPOINTER_OUT_OF_LINE

#include "scn/step/weapon/StickEnemyAlgorithm.h"

#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "hel/math/Vector3.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/weapon/MapColl.h"
#include "scn/step/weapon/Weapon.h"

using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {

StickEnemyAlgorithm::StickEnemyAlgorithm(Weapon& weapon, const ObjRefHandle<enemy::Enemy>& enemy)
    : mObj(weapon)
    , mEnemy(enemy)
    , mOffset() {
    mObj.mapColl().setValid(false);
    mObj.objColl().clearAttack();
    mObj.move().resetVelocity();
}

StickEnemyAlgorithm::~StickEnemyAlgorithm() {}

bool StickEnemyAlgorithm::procAnim() {
    if (!mEnemy.isAlive()) {
        mObj.dead();
        return true;
    }
    return false;
}

void StickEnemyAlgorithm::procMove() {
    mObj.move().decel(gobj::MoveParamDecel::Zero());
}

void StickEnemyAlgorithm::procConstraint() {
    if (mEnemy.isAlive()) {
        const enemy::Enemy& enemy = *mEnemy.operator->();
        mObj.location().setPos(enemy.location().pos() + mOffset);
    }
}

void StickEnemyAlgorithm::setOffset(const Vector3& offset) {
    mOffset = offset;
}

}}}  // namespace scn::step::weapon
