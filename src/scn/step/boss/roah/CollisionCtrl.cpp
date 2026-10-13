#include "scn/step/boss/roah/CollisionCtrl.h"

#include "hel/math/Math.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/roah/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

CollisionCtrl::CollisionCtrl(Boss& boss) : mBoss(boss), mState(STATE_0), mIsHit(false) {}

CollisionCtrl::~CollisionCtrl() {}

void CollisionCtrl::update() {
    const Param& param = mBoss.param().roah();
    bool isHit = hel::math::Math::Abs(mBoss.location().pos().z) < param.mHitDepth;
    if (isHit != mIsHit) {
        mIsHit = isHit;
        setHit();
    }
}

void CollisionCtrl::setState(State state) {
    if (mState != state) {
        mState = state;
        setHit();
    }
}

void CollisionCtrl::setHit() {
    mBoss.objColl().clearBodyColl();
    if (mIsHit) {
        const CollParam* coll = param();
        if (coll != 0) {
            if (mState == STATE_3) {
                mBoss.objColl().addBodyColl(0, coll->mRadius0, coll->mOffset0, coll->mOffset0End);
            } else {
                mBoss.objColl().addBodyColl(10, coll->mRadius0, coll->mOffset0, coll->mOffset0End);
                mBoss.objColl().addBodyColl(11, coll->mRadius1, coll->mOffset1, coll->mOffset1End);
                mBoss.objColl().addBodyColl(9, coll->mRadius2, coll->mOffset2, coll->mOffset2End);
            }
            setAttackType();
            setResistLv();
        }
    }
}

const CollParam* CollisionCtrl::param() {
    const Param& param = mBoss.param().roah();
    const CollParam* coll = 0;
    switch (mState) {
    case STATE_1:
    case STATE_2:
        coll = &param.mColl;
        break;
    case STATE_3:
        coll = &param.mCollTackle;
        break;
    }
    return coll;
}

void CollisionCtrl::setAttackType() {
    ocoll::AttackType type = static_cast<ocoll::AttackType>(0x1F4);
    if (mState == STATE_3) {
        type = static_cast<ocoll::AttackType>(0x1F9);
    }
    mBoss.objColl().bodyColl().changeAttackType(type);
}

void CollisionCtrl::setResistLv() {
    ocoll::HitResistLv lv = ocoll::HIT_RESIST_LV_2;
    if (mState == STATE_1 || mState == STATE_3) {
        lv = ocoll::HIT_RESIST_LV_6;
    }
    mBoss.objColl().bodyColl().setResistLv(lv);
}

}}}}  // namespace scn::step::boss::roah
