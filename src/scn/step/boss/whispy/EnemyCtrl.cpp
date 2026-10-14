#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS
#define HEL_COMMON_MUTABLEARRAY_REMOVEATINDEX_IN_CLASS

#include "scn/step/boss/whispy/EnemyCtrl.h"

#include "app/Random.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/MapColl.h"
#include "scn/step/map/BinEnemyVariation.h"
#include "util/ObjList.h"

using app::Random;
using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

struct ObverseData {
    map::BinEnemyKind mKind;
    map::BinEnemyVariation mVariation;
    f32 mOffsY;
};

const ObverseData T_OBVERSE_TABLE[] = {
    { static_cast<map::BinEnemyKind>(2), static_cast<map::BinEnemyVariation>(0x151), 6.75f },
    { static_cast<map::BinEnemyKind>(1), static_cast<map::BinEnemyVariation>(0x152), 6.75f },
    { static_cast<map::BinEnemyKind>(9), static_cast<map::BinEnemyVariation>(0x153), 7.5f },
    { static_cast<map::BinEnemyKind>(10), static_cast<map::BinEnemyVariation>(0x154), 4.75f },
    { static_cast<map::BinEnemyKind>(0x6A), static_cast<map::BinEnemyVariation>(1), 4.75f },
    { static_cast<map::BinEnemyKind>(0x6B), static_cast<map::BinEnemyVariation>(1), 4.75f },
    { static_cast<map::BinEnemyKind>(0x15), static_cast<map::BinEnemyVariation>(0x155), 6.75f },
};

}

EnemyCtrl::EnemyCtrl(Boss& boss) : mBoss(boss), mEnemies(), mXOffsTable(), mXOffsIndex(0) {
    initXOffsTable();
}

void EnemyCtrl::request(map::BinEnemyKind kind, map::BinEnemySize size, u32 arg) {
    cleanup();
    if (mEnemies.isFull()) {
        return;
    }
    map::BinEnemyVariation variation = static_cast<map::BinEnemyVariation>(0);
    f32 offsY = 6.75f;
    for (u32 i = 0; i < 7; i++) {
        if (kind == T_OBVERSE_TABLE[i].mKind) {
            variation = T_OBVERSE_TABLE[i].mVariation;
            offsY = T_OBVERSE_TABLE[i].mOffsY;
            break;
        }
    }
    Vector2 pos = mBoss.location().pos().getXY();
    pos.x += mXOffsTable[mXOffsIndex];
    pos.y += offsY;
    mXOffsIndex++;
    if (mXOffsIndex >= 6) {
        mXOffsIndex = 0;
    }
    enemy::Desc desc(kind, variation, arg, static_cast<map::BinEnemyDirType>(0), size, false, false, pos);
    ObjRefHandle<enemy::Enemy> enemy = mBoss.comp().enemyManager().request(desc);
    if (enemy.isAlive()) {
        enemy->mapColl().setPassInvisibleLand(false);
    }
    if (enemy.isAlive()) {
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

void EnemyCtrl::initXOffsTable() {
    static const f32 distance = 1.5f;
    static const f32 farDist = 10.5f;
    for (u32 i = 0; i < 6; i++) {
        mXOffsTable[i] = distance * i - farDist;
    }
    for (u32 i = 0; i < 20; i++) {
        u32 a = Random::RandU32(6);
        u32 b = Random::RandU32(6);
        f32 offs = mXOffsTable[a];
        mXOffsTable[a] = mXOffsTable[b];
        mXOffsTable[b] = offs;
    }
    mXOffsIndex = 0;
}

}}}}  // namespace scn::step::boss::whispy
