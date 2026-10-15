#include "scn/step/boss/goliath/IcicleCtrl.h"

#include "app/Random.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/chara/Location.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/enemy/Signal.h"

using app::Random;
using hel::common::DynamicCastToRef;
using hel::common::MutableArray;
using hel::math::Math;
using hel::math::Vector2;
using util::ObjRefHandle;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

IcicleCtrl::IcicleCtrl(Boss& boss) : mBoss(boss) {}

void IcicleCtrl::updateRequest() {
    if (mRequests.count() != 0) {
        u32 index = mRequests.count() - 1;
        request(mRequests[index]);
        mRequests.removeAtIndex(index);
    }
}

void IcicleCtrl::startRequest() {
    static const u32 maxcount = 20;
    static const f32 goliathHalfWidth = 1.95f;
    static const u32 reqMaxNum = 4;
    Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
    bool isWide = custom.landCtrl().getWidth() >= 14.5f;
    mRequests.clear();
    f32 interval = isWide ? 2.0f : 1.8f;
    f32 limit = 0.5f * custom.landCtrl().getWidth() - 0.75f;
    MutableArray<f32, 20> points;
    f32 x = 0.0f;
    points.add(x);
    while (true) {
        x += interval;
        if (x > limit) {
            break;
        }
        points.add(x);
        points.add(-x);
    }
    u32 count = 0;
    if (!isWide) {
        for (u32 i = 0; i < points.count(); i++) {
            f32 pointX = points[i] + custom.landCtrl().getCenterX();
            f32 distance = Math::Abs(pointX - mBoss.location().pos().x);
            if (distance < goliathHalfWidth) {
                points.removeAtIndex(i);
            } else if (distance < goliathHalfWidth + interval) {
                points.removeAtIndex(i);
                request(pointX);
                count++;
            }
        }
    }
    while (count < reqMaxNum) {
        if (points.count() == 0) {
            break;
        }
        u32 index = Random::RandU32(points.count());
        f32 pointX = points[index] + custom.landCtrl().getCenterX();
        points.removeAtIndex(index);
        if (Math::Abs(pointX - mBoss.location().pos().x) > goliathHalfWidth) {
            mRequests.add(pointX);
            count++;
        }
    }
}

void IcicleCtrl::request(f32 x) {
    cleanup();
    if (!mIcicles.isFull()) {
        bool isExtra;
        Custom& custom = DynamicCastToRef<Custom, ICustom>(mBoss.custom());
        isExtra = Utility::IsVariationExtra(mBoss);
        Vector2 pos;
        pos.x = x;
        pos.y = 8.25f + custom.landCtrl().getFloorY();
        enemy::Desc desc(static_cast<map::BinEnemyKind>(0x84), static_cast<map::BinEnemyVariation>(0x178), isExtra,
                         static_cast<map::BinEnemyDirType>(0), static_cast<map::BinEnemySize>(0), false, false, pos);
        ObjRefHandle<enemy::Enemy> enemy = mBoss.comp().enemyManager().request(desc);
        if (enemy.isAlive()) {
            mIcicles.add(enemy);
        }
    }
}

void IcicleCtrl::down() {
    cleanup();
    for (u32 i = 0; i < mIcicles.count(); i++) {
        mIcicles[i]->signal().set(2);
    }
}

void IcicleCtrl::fall() {
    cleanup();
    for (u32 i = 0; i < mIcicles.count(); i++) {
        mIcicles[i]->signal().set(3);
    }
}

void IcicleCtrl::cleanup() {
    for (u32 i = mIcicles.count(); i != 0; i--) {
        u32 index = i - 1;
        if (!mIcicles[index].isAlive()) {
            mIcicles.removeAtIndex(index);
        }
    }
}

}}}}  // namespace scn::step::boss::goliath
