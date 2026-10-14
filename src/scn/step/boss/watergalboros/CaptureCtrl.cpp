#include "scn/step/boss/watergalboros/CaptureCtrl.h"

#include "hel/math/Vector3.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/hero/Hero.h"

using hel::math::Vector3;

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

CaptureCtrl::CaptureCtrl(Boss& boss) : mBoss(boss), mAttacker(boss.comp(), boss.objColl().searchHit()) {}

CaptureCtrl::~CaptureCtrl() {}

void CaptureCtrl::update() {
    const Param& param = mBoss.param().watergalboros();
    Vector3 pos = mBoss.location().pos();
    pos += Vector3(param._D0);
    mAttacker.setConstraintPos(pos);
}

bool CaptureCtrl::checkCapture() {
    if (mAttacker.chkCaptureHero()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x21));
        return true;
    }
    return false;
}

void CaptureCtrl::setDamage(u32 damage) {
    mAttacker.reqDamage(damage);
}

u32 CaptureCtrl::getResistPower() const {
    return mAttacker.getResistPower();
}

void CaptureCtrl::setInvisibility() {
    if (mAttacker.isCapture()) {
        mAttacker.heroObj()->setVisibility(false);
    }
}

void CaptureCtrl::vomit() {
    if (mAttacker.isCapture()) {
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x22));
        mAttacker.clearCapture();
    }
}

void CaptureCtrl::vomitSoft() {
    if (mAttacker.isCapture()) {
        mAttacker.setSuccess();
        mAttacker.reqChangeState(static_cast<hero::CaptureHeroStateKind>(0x22));
        mAttacker.clearCapture();
    }
}

}}}}  // namespace scn::step::boss::watergalboros
