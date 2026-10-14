#include "scn/step/boss/galactaknight/CollisionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/galactaknight/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

CollisionCtrl::CollisionCtrl(Boss& boss) : mBoss(boss), mState(STATE_NONE), mIsAttack(false), mIsHit(false) {
    boss.objColl().bodyColl().setStateHitOnly();
    setAttackType();
    setCollision();
}

CollisionCtrl::~CollisionCtrl() {}

void CollisionCtrl::update() {
    const Param& param = mBoss.param().galactaknight();
    bool isHit = Math::Abs(mBoss.location().pos().z) < param._17C;
    if (isHit != mIsHit) {
        mIsHit = isHit;
        setHit();
    }
    bool isAttack = Math::Abs(mBoss.location().pos().z) < param._180;
    if (isAttack != mIsAttack) {
        mIsAttack = isAttack;
        setAttack();
    }
}

void CollisionCtrl::onStateChange() {
    for (u32 i = 1; i < mBoss.objColl().attackNum(); i++) {
        mBoss.objColl().clearAttack(i);
    }
}

void CollisionCtrl::setState(State state) {
    if (mState != state) {
        mState = state;
        setCollision();
    }
}

void CollisionCtrl::setCollision() {
    setHit();
    setAttack();
}

void CollisionCtrl::setHit() {
    mBoss.objColl().clearBodyColl();
    if (mIsHit) {
        const CollParam* coll = param();
        if (coll != 0) {
            if (!Math::EqZero(coll->mBodyRadius)) {
                mBoss.objColl().addBodyColl(2, coll->mBodyRadius, coll->mBodyOffset, coll->mBodyOffsetEnd);
                setResistLv();
            }
        }
    }
}

void CollisionCtrl::setAttack() {
    mBoss.objColl().clearAttack();
    if (mIsAttack) {
        const CollParam* coll = param();
        if (coll != 0) {
            if (!Math::EqZero(coll->mAttackRadius)) {
                mBoss.objColl().addAttack(0, 2, coll->mAttackRadius, coll->mAttackOffset, coll->mAttackOffsetEnd);
                setAttackType();
            }
        }
    }
}

const CollParam* CollisionCtrl::param() {
    const Param& param = mBoss.param().galactaknight();
    const CollParam* coll = 0;
    switch (mState) {
    case STATE_NORMAL:
    case STATE_GUARD:
    case STATE_REFLECT:
        coll = &param.mColl;
        break;
    }
    return coll;
}

void CollisionCtrl::setAttackType() {
    mBoss.objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x212));
}

void CollisionCtrl::setResistLv() {
    ocoll::HitResistLv lv = ocoll::HIT_RESIST_LV_2;
    switch (mState) {
    case STATE_GUARD:
    case STATE_REFLECT:
        lv = ocoll::HIT_RESIST_LV_6;
        break;
    }
    mBoss.objColl().bodyColl().setResistLv(lv);
}

}}}}  // namespace scn::step::boss::galactaknight
