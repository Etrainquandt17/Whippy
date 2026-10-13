#include "scn/step/boss/watergalboros/CaptureCtrl.h"

#include "g3d/NodeAccessor.h"
#include "g3d/NodeLocalMtxAccessor.h"
#include "gobj/Anim.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/BodyColl.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/chara/HitPoint.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"
#include "scn/step/chara/ModelRotCtrl.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/ScriptTrigger.h"
#include "scn/step/chara/Shadow.h"
#include "scn/step/chara/WorldCage.h"
#include "scn/step/enemy/Desc.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Manager.h"
#include "scn/step/hero/Hero.h"
#include "util/ObjRefHandle.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

CaptureCtrl::CaptureCtrl(Boss& boss) : mBoss(boss), mAttacker(boss.comp(), boss.objColl().searchHit()) {}

CaptureCtrl::~CaptureCtrl() {}

void CaptureCtrl::update() {
    const Param& param = mBoss.param().watergalboros();
    hel::math::Vector3 pos = mBoss.location().pos();
    pos += hel::math::Vector3(param._D0);
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
