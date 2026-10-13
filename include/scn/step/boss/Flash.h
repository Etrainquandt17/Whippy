#ifndef SCN_STEP_BOSS_FLASH_H
#define SCN_STEP_BOSS_FLASH_H

#include "gobj/ColorAnim.h"
#include "scn/step/boss/AttackFlash.h"
#include "scn/step/boss/CustomFlash.h"
#include "scn/step/boss/DamageFlash.h"
#include "scn/step/boss/DeadFlash.h"
#include "scn/step/boss/GuardFlash.h"
#include "util/PlacementNew.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class Flash {
public:
    Flash(Boss& boss, mem::IAllocator& allocator);

    void procAnim();
    void procReadyToRender();
    void updateUseGPU();
    void onStateChange();
    DamageFlash& damage();
    DeadFlash& dead();
    AttackFlash& attack();
    GuardFlash& guard();
    CustomFlash& custom();

private:
    Boss& mBoss;
    util::PlacementNew<gobj::ColorAnim> mColorAnim;
    DamageFlash mDamage;
    DeadFlash mDead;
    AttackFlash mAttack;
    GuardFlash mGuard;
    CustomFlash mCustom;
    GXColor mColor;
    g3d::ColorAnimFlashOp mOperation;
};

}
}
}

#endif
