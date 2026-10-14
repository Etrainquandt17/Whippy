#include "scn/step/boss/metalgeneral/CollisionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/metalgeneral/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Math;

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

// TODO: the names are guesses.
enum CollId {
    COLL_ID_PATRIOT = 5,
    COLL_ID_NORMAL = 6
};

}

CollisionCtrl::CollisionCtrl(Boss& boss) : mBoss(boss), mState(STATE_0), mIsHit(false) {
    mBoss.objColl().bodyColl().setStateHitOnly();
}

CollisionCtrl::~CollisionCtrl() {}

void CollisionCtrl::update() {
    const Param& param = mBoss.param().metalgeneral();
    bool isHit = Math::Abs(mBoss.location().pos().z) < param.mHitDepth;
    if (isHit != mIsHit) {
        mIsHit = isHit;
        setHit();
        setAttack();
    }
}

void CollisionCtrl::setState(State state) {
    if (mState != state) {
        mState = state;
        setHit();
        setAttack();
    }
}

void CollisionCtrl::setHit() {
    mBoss.objColl().clearBodyColl();
    if (mIsHit) {
        const CollParam* coll = param();
        if (coll != 0) {
            CollId id = mState == STATE_4 ? COLL_ID_PATRIOT : COLL_ID_NORMAL;
            mBoss.objColl().addBodyColl(id, coll->mBodyRadius, coll->mBodyOffset, coll->mBodyOffsetEnd);
            setResistLv();
        }
    }
}

void CollisionCtrl::setAttack() {
    mBoss.objColl().clearAttack(0);
    if (mIsHit) {
        const CollParam* coll = param();
        if (coll != 0) {
            CollId attack = mState == STATE_4 ? COLL_ID_PATRIOT : COLL_ID_NORMAL;
            mBoss.objColl().addAttack(0, attack, coll->mAttackRadius, coll->mAttackOffset, coll->mAttackOffsetEnd);
            setAttackType();
        }
    }
}

const CollParam* CollisionCtrl::param() {
    const Param& param = mBoss.param().metalgeneral();
    const CollParam* coll = 0;
    switch (mState) {
    case STATE_1:
    case STATE_2:
    case STATE_3:
        coll = &param.mColl;
        break;
    case STATE_4:
    case STATE_5:
        coll = &param.mCollPatriot;
        break;
    }
    return coll;
}

void CollisionCtrl::setAttackType() {
    ocoll::AttackType type = static_cast<ocoll::AttackType>(0x1DB);
    switch (mState) {
    case STATE_3:
        type = static_cast<ocoll::AttackType>(0x1DD);
        break;
    case STATE_5:
        type = static_cast<ocoll::AttackType>(0x1DF);
        break;
    }
    mBoss.objColl().setAttackType(0, type);
}

void CollisionCtrl::setResistLv() {
    ocoll::HitResistLv lv = ocoll::HIT_RESIST_LV_2;
    if (mState == STATE_1) {
        lv = ocoll::HIT_RESIST_LV_6;
    }
    mBoss.objColl().bodyColl().setResistLv(lv);
}

}}}}  // namespace scn::step::boss::metalgeneral
