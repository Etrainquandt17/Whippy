#include "scn/step/boss/whispy/DamageEyeCtrl.h"

#include "gobj/Anim.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace whispy {

DamageEyeCtrl::DamageEyeCtrl(Boss& boss) : mBoss(boss), mIsSet(false) {}

void DamageEyeCtrl::update() {
    if (mIsSet) {
        if (mBoss.model().anim().subAnimAccessor(0).isAnimEnd()) {
            mBoss.model().anim().subAnimClear(0);
            mIsSet = false;
        }
    }
}

void DamageEyeCtrl::set() {
    mBoss.model().anim().subAnimSet(0, 0x15, 1);
    mBoss.model().anim().subAnimAccessor(0).start(false);
    mIsSet = true;
}

}
}
}
}
