#include "scn/step/boss/lowper/CollisionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/lowper/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace lowper {

CollisionCtrl::CollisionCtrl(Boss& boss) : mBoss(boss), mState(STATE_NONE), mIsAttack(false), mIsHit(false) {
    boss.objColl().bodyColl().setTeamXlu(static_cast<ocoll::TeamFlag>(6));
    mBoss.objColl().bodyColl().setStateHitOnly();
    setAttackType();
    setCollision();
}

CollisionCtrl::~CollisionCtrl() {}

void CollisionCtrl::update() {
    const Param& param = mBoss.param().lowper();
    bool isHit = Math::Abs(mBoss.location().pos().z) < param._90;
    if (isHit != mIsHit) {
        mIsHit = isHit;
        setHit();
    }
    bool isAttack = Math::Abs(mBoss.location().pos().z) < param._94;
    if (isAttack != mIsAttack) {
        mIsAttack = isAttack;
        setAttack();
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
            mBoss.objColl().bodyColl().setStateHitOnly();
            mBoss.objColl().addBodyColl(0, coll->mBodyRadius, coll->mBodyOffset, coll->mBodyOffsetEnd);
        }
    }
}

void CollisionCtrl::setAttack() {
    mBoss.objColl().clearAttack(0);
    if (mIsAttack) {
        const CollParam* coll = param();
        if (coll != 0) {
            mBoss.objColl().addAttack(0, 0, coll->mAttackRadius, coll->mAttackOffset, coll->mAttackOffsetEnd);
            setAttackType();
        }
    }
}

const CollParam* CollisionCtrl::param() {
    const Param& param = mBoss.param().lowper();
    const CollParam* coll = 0;
    switch (mState) {
    case STATE_NORMAL:
        coll = &param._98;
        break;
    case STATE_TACKLE:
        coll = &param._98;
        break;
    case STATE_TACKLE_FAR:
        coll = &param._C0;
        break;
    case STATE_TACKLE_FAR_ROLLING:
        coll = &param._E8;
        break;
    case STATE_FIRE_TACKLE:
        coll = &param._110;
        break;
    }
    return coll;
}

void CollisionCtrl::setAttackType() {
    ocoll::AttackType type = static_cast<ocoll::AttackType>(0x1B7);
    switch (mState) {
    case STATE_TACKLE:
    case STATE_TACKLE_FAR:
    case STATE_TACKLE_FAR_ROLLING:
        type = static_cast<ocoll::AttackType>(0x1B8);
        break;
    case STATE_FIRE_TACKLE:
        type = static_cast<ocoll::AttackType>(0x1BD);
        break;
    }
    mBoss.objColl().setAttackType(0, type);
}

}}}}  // namespace scn::step::boss::lowper
