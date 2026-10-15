#define HEL_MATH_VECTOR2_GETNORMALIZED_IN_CLASS
#include "scn/step/boss/goliath/CollisionCtrl.h"

#include "gobj/GearModel.h"
#include "hel/math/Vector2.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ObjColl.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace boss {
namespace goliath {

CollisionCtrl::CollisionCtrl(Boss& boss) : mBoss(boss), mState(STATE_NONE) {}

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
    mBoss.objColl().clearBodyColl();
    mBoss.objColl().clearAttack(0);
    if (mState != STATE_NONE) {
        mBoss.objColl().setBodyCollStateHitOnly();
        mBoss.objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1E9));
        mBoss.objColl().setAttackCenter(1, Vector2::ZERO);
        mBoss.objColl().addBodyColl(1, 1.5f);
        mBoss.objColl().addAttack(0, 1, 1.25f);
        setResistLv();
        if (mState == STATE_PUNCH) {
            Vector2 hand = mBoss.model().model().nodes().at(5).worldTrans().getXY();
            Vector2 body = mBoss.model().model().nodes().at(1).worldTrans().getXY();
            if (!(hand - body).isZeroLoose(0.00001f)) {
                hand += (hand - body).getNormalized() * 1.5f;
            }
            mBoss.objColl().addBodyColl(0, 0.5f, hand - mBoss.location().pos().getXY(), body - mBoss.location().pos().getXY(),
                                        false);
        }
    }
}

void CollisionCtrl::setResistLv() {
    ocoll::HitResistLv lv = ocoll::HIT_RESIST_LV_NORMAL;
    if (mState == STATE_REFLECT) {
        lv = ocoll::HIT_RESIST_LV_REFLECT;
    }
    mBoss.objColl().bodyColl().setResistLv(lv);
}

}}}}  // namespace scn::step::boss::goliath
