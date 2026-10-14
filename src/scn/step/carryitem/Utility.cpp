#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/carryitem/Utility.h"

#include "gobj/Location.h"
#include "hel/geo/Rect.h"
#include "ocoll/SearchHit.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Manager.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/carryitem/CarryItem.h"
#include "scn/step/carryitem/VacuumReceiver.h"
#include "scn/step/chara/ObjCollLite.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"

using hel::geo::Rect;
using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace carryitem {

bool Utility::IsSearchCollide(CarryItem& carryItem) {
    ::ocoll::SearchHit& searchHit = carryItem.objColl().searchHit();
    if (!searchHit.isCollide()) {
        return false;
    }
    for (u32 i = 0; i < searchHit.getCollidedNum(); i++) {
        u64 uid = searchHit.getCollidedHitOwnerUid(i);
        bool isEnemy = false;
        ObjRefHandle<enemy::Enemy> enemy = carryItem.comp().enemyManager().getEnemyByOCollOwnerUID(uid);
        if (enemy.isAlive()) {
            isEnemy = enemy->kind() != 0x64;
        }
        bool isBoss = carryItem.comp().bossManager().getBossByObjCollOwnerID(uid).isAlive();
        if (isEnemy || isBoss) {
            return true;
        }
    }
    return false;
}

bool Utility::InScreen(CarryItem& carryItem, f32 margin) {
    Rect rect = carryItem.comp().mainCamera().getViewRect();
    rect._8 -= margin;
    rect._C += margin;
    rect._0 += margin;
    rect._4 -= margin;
    Vector2 pos = carryItem.location().pos().getXY();
    return rect.isInclude(pos.x, pos.y);
}

void Utility::OnCrash(CarryItem& carryItem) {
    carryItem.setIsEnableCarry(false);
    carryItem.setCanGather(false);
    carryItem.vacuumReceiver().setIsValid(false);
}

}}}  // namespace scn::step::carryitem
