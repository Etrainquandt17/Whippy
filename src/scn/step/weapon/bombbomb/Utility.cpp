#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/weapon/bombbomb/Utility.h"

#include "ocoll/SearchHit.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjRefHandle.h"

using util::ObjRefHandle;

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

bool Utility::IsSearchCollide(Weapon& weapon) {
    const ::ocoll::SearchHit& searchHit = weapon.objColl().searchHit();
    if (!searchHit.isCollide()) {
        return false;
    }
    for (u32 i = 0; i < searchHit.getCollidedNum(); i++) {
        u64 uid = searchHit.getCollidedHitOwnerUid(i);
        ObjRefHandle<enemy::Enemy> enemy = weapon.comp().enemyManager().getEnemyByOCollOwnerUID(uid);
        bool isEnemy = false;
        if (enemy.isAlive()) {
            isEnemy = enemy->kind() != 0x64;
        }
        bool isBoss = weapon.comp().bossManager().getBossByObjCollOwnerID(uid).isAlive();
        if (isEnemy || isBoss) {
            return true;
        }
    }
    return false;
}

}}}}  // namespace scn::step::weapon::bombbomb
