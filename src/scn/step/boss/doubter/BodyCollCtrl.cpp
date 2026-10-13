#include "scn/step/boss/doubter/BodyCollCtrl.h"

#include "hel/math/Vector2.h"
#include "scn/step/boss/Angry.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/ocoll/AttackType.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

BodyCollCtrl::BodyCollCtrl(Boss& boss) : mBoss(boss), mState(STATE_0) {}

void BodyCollCtrl::onStateChange() {
    for (u32 i = 1; i < mBoss.objColl().attackNum(); i++) {
        mBoss.objColl().clearAttack(i);
    }
}

void BodyCollCtrl::setState(State state) {
    if (mState == state) {
        return;
    }
    mState = state;
    switch (state) {
    case STATE_0:
        setHide();
        break;
    case STATE_1:
        setDefault();
        break;
    case STATE_2:
        setDefaultWithoutHandAttack();
        break;
    case STATE_3:
        setTornado();
        break;
    }
}

void BodyCollCtrl::setHide() {
    mBoss.objColl().clearBodyColl();
    mBoss.objColl().clearAttack(0);
}

void BodyCollCtrl::setDefault() {
    const Param& param = mBoss.param().doubter();
    mBoss.objColl().clearBodyColl();
    mBoss.objColl().clearAttack(0);
    mBoss.objColl().setBodyCollStateNormal();
    mBoss.objColl().bodyColl().initAttackType(static_cast<ocoll::AttackType>(0x1C9));
    f32 scale = mBoss.angry().isAngry() ? param.mScaleAnger : 1.0f;
    mBoss.objColl().addBodyColl(8, param._198 * scale);
    mBoss.objColl().addBodyColl(9, param._19C * scale);
    mBoss.objColl().addBodyColl(10, param._1A0 * scale);
    mBoss.objColl().addBodyColl(11, param._1A4 * scale);
    mBoss.objColl().addBodyColl(6, param._1A8 * scale);
    mBoss.objColl().addBodyColl(7, param._1A8 * scale);
}

void BodyCollCtrl::setDefaultWithoutHandAttack() {
    const Param& param = mBoss.param().doubter();
    mBoss.objColl().clearBodyColl();
    mBoss.objColl().clearAttack(0);
    mBoss.objColl().setBodyCollStateHitOnly();
    mBoss.objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1C9));
    mBoss.objColl().setAttackCenter(8, hel::math::Vector2::ZERO);
    f32 scale = mBoss.angry().isAngry() ? param.mScaleAnger : 1.0f;
    mBoss.objColl().addBodyColl(8, param._198 * scale);
    mBoss.objColl().addBodyColl(9, param._19C * scale);
    mBoss.objColl().addBodyColl(10, param._1A0 * scale);
    mBoss.objColl().addBodyColl(11, param._1A4 * scale);
    mBoss.objColl().addBodyColl(6, param._1A8 * scale);
    mBoss.objColl().addBodyColl(7, param._1A8 * scale);
    mBoss.objColl().addAttack(0, 8, param._198 * scale);
    mBoss.objColl().addAttack(0, 9, param._19C * scale);
    mBoss.objColl().addAttack(0, 10, param._1A0 * scale);
    mBoss.objColl().addAttack(0, 11, param._1A4 * scale);
}

void BodyCollCtrl::setTornado() {
    const Param& param = mBoss.param().doubter();
    mBoss.objColl().clearBodyColl();
    mBoss.objColl().clearAttack(0);
    mBoss.objColl().setBodyCollStateHitOnly();
    mBoss.objColl().setAttackType(0, static_cast<ocoll::AttackType>(0x1CA));
    mBoss.objColl().setAttackCenter(8, hel::math::Vector2::ZERO);
    f32 scale = mBoss.angry().isAngry() ? param.mScaleAnger : 1.0f;
    mBoss.objColl().addBodyColl(8, param._198 * scale);
    mBoss.objColl().addBodyColl(9, param._19C * scale);
    mBoss.objColl().addBodyColl(10, param._1A0 * scale);
    mBoss.objColl().addBodyColl(11, param._1A4 * scale);
    mBoss.objColl().addBodyColl(6, param._1A8 * scale);
    mBoss.objColl().addBodyColl(7, param._1A8 * scale);
    mBoss.objColl().addAttack(0, 8, param._198 * scale);
    mBoss.objColl().addAttack(0, 9, param._19C * scale);
    mBoss.objColl().addAttack(0, 10, param._1A0 * scale);
    mBoss.objColl().addAttack(0, 11, param._1A4 * scale);
    mBoss.objColl().addAttack(0, 0, param._1AC * scale, hel::math::Vector2(0.0f, param._1AC * scale));
}

}
}
}
}
