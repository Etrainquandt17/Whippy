#include "scn/step/enemy/tsukikage/Custom.h"

#include "app/Random.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/Shadow.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/damage/StateDeadInWater.h"
#include "scn/step/enemy/tsukikage/ParamData.h"
#include "scn/step/weapon/Desc.h"
#include "scn/step/weapon/Manager.h"

using app::Random;
using hel::common::RuntimeTypeInfo;
using hel::common::RuntimeTypeInfoImpl;
using hel::math::Math;
using hel::math::Vector2;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

Custom::Custom(Enemy& enemy)
    : CustomBase(enemy), mIsWall(true), mIsNear(false), mIsFirstAppear(false), mIsWarp(false),
      mBasePos(enemy.location().pos()), mPrevJumpNum(0), mJumpNum(1) {}

bool Custom::onInit() {
    if (obj().variation() == 0x88) {
        Vector3 pos = obj().location().pos();
        if (obj().dirType() == static_cast<map::BinEnemyDirType>(3)) {
            pos.x -= 0.1f;
        } else if (obj().dirType() == static_cast<map::BinEnemyDirType>(2)) {
            pos.x += 0.1f;
        }
        obj().location().setPos(pos);
    }
    return false;
}

bool Custom::onDamaged() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
    obj().model().rotCtrl().setValid(true);
    mIsWall = false;
    return false;
}

bool Custom::onVacuumReceive() {
    obj().model().setVisibility(true);
    obj().shadow().setVisibility(true);
    return false;
}

bool Custom::onHitPointIsZero() {
    return onVacuumReceive();
}

bool Custom::onInWater() {
    if (!mIsWarp) {
        obj().stateChanger().setNextState<damage::StateDeadInWater, Enemy*>(&obj());
        return true;
    }
    return false;
}

void Custom::setWall(bool isWall) {
    mIsWall = isWall;
}

bool Custom::isWall() {
    int x = static_cast<int>(obj().location().pos().x);
    int y = static_cast<int>(obj().location().centerPos().y);
    int checkX = obj().dirType() == static_cast<map::BinEnemyDirType>(3) ? x - 1 : x + 1;
    if (mIsWall && !Utility::IsExistLand(obj(), checkX, y)) {
        mIsWall = false;
    }
    return mIsWall;
}

void Custom::requestShuriken() {
    const ParamData& param = obj().param().tsukikage();
    Vector3 p = obj().location().pos();
    Vector2 pos(p.x, p.y);
    Vector2 velocity;
    pos.x += param.mShurikenOffsetX * obj().target().getSign();
    pos.y += param.mShurikenOffsetY;
    velocity = Vector2(param.mShurikenSpeed * obj().target().getSign(), 0.0f);
    weapon::Desc desc(static_cast<weapon::Kind>(0x3b), 0, static_cast<ostop::Flag>(4), pos, pos, velocity, obj().objColl().owner());
    obj().comp().weaponManager().request(desc);
}

s32 Custom::getJumpNum() {
    f32 distance = Math::Abs(Utility::GetNearestPlayerPos(obj()).x - obj().location().pos().x);
    if (distance <= obj().param().tsukikage().mJumpNearDistance) {
        mIsNear = true;
    } else {
        mIsNear = false;
    }
    s32 num = setJumpNum();
    while (mPrevJumpNum == mJumpNum && mJumpNum == num) {
        num = setJumpNum();
    }
    mPrevJumpNum = mJumpNum;
    mJumpNum = num;
    return num;
}

bool Custom::isJumpAttack() {
    const ParamData& param = obj().param().tsukikage();
    f32 y = obj().location().pos().y;
    f32 playerY = Utility::GetNearestPlayerPos(obj()).y;
    s32 rand = Random::Rand(param.mJumpAttackRand);
    bool result = false;
    if (playerY >= y + param.mJumpAttackHeight) {
        if (rand >= param.mJumpAttackRateHigh) {
            result = true;
        }
    } else {
        if (rand >= param.mJumpAttackRateLow) {
            result = true;
        }
    }
    return result;
}

bool Custom::isWallAttack() {
    const ParamData& param = obj().param().tsukikage();
    s32 dir = -1;
    if (obj().dirType() == static_cast<map::BinEnemyDirType>(3)) {
        dir = 1;
    }
    bool result = false;
    Vector3 pos = obj().location().pos();
    Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
    f32 left = pos.x + param.mWallAttackRangeNear * dir;
    f32 right = pos.x + param.mWallAttackRangeFar * dir;
    f32 top = pos.y + param.mWallAttackRangeTop;
    f32 bottom = pos.y + param.mWallAttackRangeBottom;
    if (left > right) {
        f32 tmp = left;
        left = right;
        right = tmp;
    }
    if (left <= playerPos.x && playerPos.x <= right && bottom <= playerPos.y && playerPos.y <= top) {
        result = true;
    }
    if (!isWall()) {
        result = false;
    }
    return result;
}

void Custom::setWarp(bool isWarp) {
    mIsWarp = isWarp;
}

bool Custom::isFirstAppear() {
    return mIsFirstAppear;
}

void Custom::setFirstAppear(bool isFirstAppear) {
    mIsFirstAppear = isFirstAppear;
}

Vector3 Custom::getBasePos() {
    return mBasePos;
}

s32 Custom::setJumpNum() {
    s32 num = 0;
    s32 rand;
    if (mIsNear) {
        rand = Random::Rand(7);
    } else {
        rand = Random::Rand(8);
    }
    if (rand >= 0 && rand <= 1) {
        num = 0;
    } else if (rand == 2) {
        num = 1;
    } else if (rand >= 3 && rand <= 4) {
        num = 2;
    } else if (rand >= 5) {
        num = 3;
    }
    return num;
}

const RuntimeTypeInfo& Custom::GetRuntimeTypeInfo() const {
    return RuntimeTypeInfoImpl<Custom>();
}

Custom::~Custom() {}

}}}}  // namespace scn::step::enemy::tsukikage
