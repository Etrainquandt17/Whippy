#ifndef SCN_STEP_WEAPON_STICKENEMYALGORITHM_H
#define SCN_STEP_WEAPON_STICKENEMYALGORITHM_H

#include "hel/math/Vector3.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {

namespace enemy {
class Enemy;
}

namespace weapon {

class Weapon;

// TODO: the unit is not written yet; the functions are the ones the map lists.
class StickEnemyAlgorithm {
public:
    StickEnemyAlgorithm(Weapon& weapon, const util::ObjRefHandle<enemy::Enemy>& enemy);
    ~StickEnemyAlgorithm();

    bool procAnim();
    void procMove();
    void procConstraint();
    void setOffset(const hel::math::Vector3& offset);

private:
    Weapon& mObj;
    util::ObjRefHandle<enemy::Enemy> mEnemy;
    hel::math::Vector3 mOffset;
};

}}}  // namespace scn::step::weapon

#endif
