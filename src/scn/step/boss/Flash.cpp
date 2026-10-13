#include "scn/step/boss/Flash.h"

#include "gobj/GearModel.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ObjStop.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {

// TODO: the zero of the initialisers and the model trade r30 and r31; everything else matches.
Flash::Flash(Boss& boss, mem::IAllocator& allocator)
    : mBoss(boss), mColorAnim(), mDamage(), mDead(), mAttack(), mGuard(), mCustom(), mColor((GXColor){ 0, 0, 0, 0 }),
      mOperation(g3d::ColorAnimFlashOp_0) {
    mColorAnim.construct<gobj::ColorAnimDesc, mem::IAllocator&, gobj::IG3DModel&>(
        gobj::ColorAnimDesc(), allocator, mBoss.model().model()
    );
}

void Flash::procAnim() {
    mDamage.update();
    mDead.update();
    if (!mBoss.objStop().isStopped() && !mBoss.hitStop().isStopped()) {
        mAttack.update();
        mGuard.update();
        mCustom.update();
    }
}

void Flash::procReadyToRender() {
    if (!mColorAnim.isConstruct()) {
        return;
    }
    if (mDead.isValid()) {
        mColor = mDead.getColor();
        mOperation = g3d::ColorAnimFlashOp_0;
    } else if (mDamage.isValid()) {
        mColor = mDamage.getColor();
        mOperation = g3d::ColorAnimFlashOp_0;
    } else if (mCustom.isValid()) {
        mColor = mCustom.getColor();
        mOperation = mCustom.getOperation();
    } else if (mAttack.isValid()) {
        mColor = mAttack.getColor();
        mOperation = g3d::ColorAnimFlashOp_0;
    } else if (mGuard.isValid()) {
        mColor = mGuard.getColor();
        mOperation = g3d::ColorAnimFlashOp_0;
    } else {
        mColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0x00 };
        mOperation = g3d::ColorAnimFlashOp_0;
    }
    g3d::ColorAnimFlash flash = mColorAnim->flash();
    flash.setColor(mColor);
    flash.setOperation(mOperation);
    mColorAnim->setFlash(flash);
}

void Flash::updateUseGPU() {
    if (mColorAnim.isConstruct()) {
        mColorAnim->updateUseGPU();
    }
}

void Flash::onStateChange() {
    mAttack.cancel();
    mGuard.setIsValid(false);
}

DamageFlash& Flash::damage() {
    return mDamage;
}

DeadFlash& Flash::dead() {
    return mDead;
}

AttackFlash& Flash::attack() {
    return mAttack;
}

GuardFlash& Flash::guard() {
    return mGuard;
}

CustomFlash& Flash::custom() {
    return mCustom;
}

}
}
}
