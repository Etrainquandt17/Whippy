#include "scn/step/boss/whispy/CaptureCtrl.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/whispy/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

CaptureCtrl::CaptureCtrl(Boss& boss) : mBoss(boss), mAttacker(boss.comp(), boss.objColl().searchHit()) {
    const Param& param = mBoss.param().whispy();
    hel::math::Vector3 pos = mBoss.location().pos();
    pos += hel::math::Vector3(param.mCaptureOffset);
    mAttacker.setConstraintPos(pos);
}

bool CaptureCtrl::checkCapture() {
    if (mAttacker.chkCaptureHero()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0));
        return true;
    }
    return false;
}

void CaptureCtrl::vomit() {
    if (mAttacker.isCapture()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(1));
        mAttacker.clearCapture();
    }
}

void CaptureCtrl::vomitSoft() {
    if (mAttacker.isCapture()) {
        mAttacker.setSuccess();
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(2));
        mAttacker.clearCapture();
    }
}

void CaptureCtrl::release() {
    if (mAttacker.isCapture()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(3));
        mAttacker.clearCapture();
    }
}

void CaptureCtrl::setDamage(u32 damage) {
    mAttacker.reqDamage(damage);
}

u32 CaptureCtrl::getResistPower() const {
    return mAttacker.getResistPower();
}

}
}
}
}
