#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/dubior/EnemyCtrl.h"

#include "gobj/Move.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "util/ObjList.h"

using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace dubior {

EnemyCtrl::EnemyCtrl(Boss& boss) : mBoss(boss), mEnemies() {}

void EnemyCtrl::request(map::BinEnemyVariation variation, Vector2 pos, Vector3 velocity) {
    cleanup();
    if (mEnemies.isFull()) {
        return;
    }
    enemy::Desc desc(static_cast<map::BinEnemyKind>(0x72), variation, 0, static_cast<map::BinEnemyDirType>(0), static_cast<map::BinEnemySize>(0),
                     false, false, pos);
    desc._28 = true;
    desc._20 = mBoss.location().pos().getXY();
    ObjRefHandle<enemy::Enemy> enemy = mBoss.comp().enemyManager().request(desc);
    if (enemy.isAlive()) {
        enemy->move().setVelocity(velocity);
        enemy::Accessor accessor(enemy.operator->());
        mEnemies.add(accessor);
    }
}

void EnemyCtrl::cleanup() {
    u32 i = mEnemies.count();
    if (i != 0) {
        for (; i != 0; i--) {
            u32 index = i - 1;
            if (!mEnemies[index].isValid()) {
                mEnemies.removeAtIndex(index);
            }
        }
    }
}

}}}}  // namespace scn::step::boss::dubior
