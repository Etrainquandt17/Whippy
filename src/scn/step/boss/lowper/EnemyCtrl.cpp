#include "scn/step/boss/lowper/EnemyCtrl.h"

#include "app/Random.h"
#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/MoveParam.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/lowper/CollisionCtrl.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/GearCtrl.h"
#include "scn/step/boss/lowper/ItemCtrl.h"
#include "scn/step/boss/lowper/MiniBlackHoleCtrl.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/WaftMoveCtrl.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/camera/QuakeKind.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustom.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/Signal.h"
#include "scn/step/enemy/lowperbullet/Custom.h"
#include "util/ObjList.h"
#include "util/ObjRefHandle.h"

using hel::common::DynamicCastToRef;
using hel::math::Math;
using hel::math::Vector3;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

}}}}  // namespace scn::step::boss::lowper

namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::step::enemy::lowperbullet::Custom>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::step::enemy::ICustom>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace step {
namespace boss {
namespace lowper {

EnemyCtrl::EnemyCtrl(Boss& boss)
    : mBoss(boss), mEnemies(), mBarriers(), mBarrierRot(0.0f), mBarrierAngle(-65.0f), mBarrierAngleTarget(-65.0f),
      mBarrierRadius(1.5f), mBarrierRotSpeed(8.0f), mIsBarrierSE(false) {}

void EnemyCtrl::update() {
    mBarrierRot += mBarrierRotSpeed;
    if (mBarrierRot >= 360.0f) {
        mBarrierRot -= 360.0f;
    }
    mBarrierAngle = Math::Interpolate(mBarrierAngle, mBarrierAngleTarget, 0.05f);
    bool isExist = false;
    for (u32 i = 0; i < 3; i++) {
        if (mBarriers[i].isValid()) {
            isExist = true;
            break;
        }
    }
    if (mIsBarrierSE && !isExist) {
        mBoss.soundSE().loop().stop();
        mIsBarrierSE = false;
    } else if (!mIsBarrierSE && isExist) {
        mBoss.soundSE().loop().start(0x56C);
        mIsBarrierSE = true;
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

void EnemyCtrl::request(enemy::lowperbullet::VariationKind kind, Vector3 pos, Vector3 speed, u32 _4) {
    cleanup();
    if (mEnemies.isFull()) {
        return;
    }
    Vector3 reqPos = pos;
    for (u32 i = 0; i < 3; i++) {
        if (mBarriers[i].isValid()) {
            reqPos += mBarriers[i].obj().location().pos() - mBoss.location().pos();
            mBarriers[i].obj().dead();
            break;
        }
    }
    u32 kinds[] = { 0x66, 0x67, 0x68, 0x69 };
    map::BinEnemyKind enemyKind = static_cast<map::BinEnemyKind>(kinds[mBoss.level()]);
    map::BinEnemyDirType dirType =
        mBoss.target().isRightDir() ? static_cast<map::BinEnemyDirType>(3) : static_cast<map::BinEnemyDirType>(2);
    enemy::Desc desc(enemyKind, static_cast<map::BinEnemyVariation>(kind), _4, dirType, static_cast<map::BinEnemySize>(0), false, false,
                     reqPos.getXY());
    ObjRefHandle<enemy::Enemy> enemy = mBoss.comp().enemyManager().request(desc);
    if (enemy.isAlive()) {
        enemy->move().setVelocity(speed);
        enemy->location().setPos(reqPos);
        enemy::lowperbullet::Custom& custom =
            DynamicCastToRef<enemy::lowperbullet::Custom, enemy::ICustom>(enemy->custom());
        custom.setTargetHero(mBoss.hateCtrl().getMostHatedHero());
    }
    if (enemy.isAlive()) {
        enemy::Accessor accessor(enemy.operator->());
        mEnemies.add(accessor);
    }
}

void EnemyCtrl::requestBarrier() {
    u32 kinds[] = { 0x66, 0x67, 0x68, 0x69 };
    map::BinEnemyKind enemyKind = static_cast<map::BinEnemyKind>(kinds[mBoss.level()]);
    enemy::Desc desc(enemyKind, static_cast<map::BinEnemyVariation>(3), 0, static_cast<map::BinEnemyDirType>(0),
                     static_cast<map::BinEnemySize>(0), false, false, getBarrierFollowCenter().getXY());
    for (u32 i = 0; i < 3; i++) {
        if (!mBarriers[i].isValid()) {
            ObjRefHandle<enemy::Enemy> enemy = mBoss.comp().enemyManager().request(desc);
            if (enemy.isAlive()) {
                DynamicCastToRef<enemy::lowperbullet::Custom, enemy::ICustom>(enemy->custom()).setParent(mBoss, i);
                mBarriers[i] = enemy::Accessor(enemy.operator->());
            }
            break;
        }
    }
}

void EnemyCtrl::sendSignalBarrierWarpIn() {
    for (u32 i = 0; i < 3; i++) {
        if (mBarriers[i].isValid()) {
            mBarriers[i].obj().signal().set(1);
        }
    }
}

void EnemyCtrl::setBarrierAngle(f32 angle) {
    mBarrierAngleTarget = angle;
}

void EnemyCtrl::resetBarrierAngle() {
    mBarrierAngleTarget = -65.0f;
}

void EnemyCtrl::setBarrierRadius(f32 radius) {
    mBarrierRadius = radius;
}

void EnemyCtrl::resetBarrierRadius() {
    mBarrierRadius = 1.5f;
}

f32 EnemyCtrl::getBarrierRadius() const {
    return mBarrierRadius;
}

void EnemyCtrl::setBarrierRotSpeed(f32 speed) {
    mBarrierRotSpeed = speed;
}

void EnemyCtrl::resetBarrierRotSpeed() {
    mBarrierRotSpeed = 8.0f;
}

Vector3 EnemyCtrl::getBarrierFollowPos(u32 index) {
    f32 rot = 120.0f * index + mBarrierRot;
    if (rot >= 360.0f) {
        rot -= 360.0f;
    }
    Vector3 offset = Vector3::BASIS_Y * mBarrierRadius;
    offset.rotate(Vector3::AXIS_Z, 0.017453292f * rot);
    offset.rotate(Vector3::AXIS_X, 0.017453292f * mBarrierAngle);
    return getBarrierFollowCenter() + offset;
}

Vector3 EnemyCtrl::getBarrierFollowCenter() {
    return mBoss.location().pos() + Vector3(0.0f, 0.25f, 0.0f);
}

u32 EnemyCtrl::getBarrierCount() const {
    u32 count = 0;
    for (u32 i = 0; i < 3; i++) {
        if (mBarriers[i].isValid()) {
            count++;
        }
    }
    return count;
}

}}}}  // namespace scn::step::boss::lowper
