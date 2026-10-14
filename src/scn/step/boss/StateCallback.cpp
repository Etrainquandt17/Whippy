#include "scn/step/boss/StateCallback.h"

#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Effect.h"
#include "scn/step/boss/Flash.h"
#include "scn/step/boss/Guard.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/Invincible.h"
#include "scn/step/boss/SoundSE.h"
#include "scn/step/boss/SuperStop.h"
#include "scn/step/chara/HitStop.h"
#include "scn/step/chara/ObjColl.h"

using util::IStateChanger;

namespace scn {
namespace step {
namespace boss {

StateCallback::StateCallback(Boss& boss) : mBoss(boss), mCanClearAttack(true) {}

void StateCallback::onStateChanged(const IStateChanger&) {
    if (mCanClearAttack) {
        mBoss.objColl().clearAttack();
    }
    mBoss.hitStop().unsetArmor();
    mBoss.objColl().clearSearchHit();
    mBoss.invincible().unsetPerm();
    mBoss.guard().setType(GUARD_TYPE_0);
    mBoss.effect().onStateChange();
    mBoss.brainCtrl().toInvalid();
    mBoss.soundSE().onStateChange();
    mBoss.flash().onStateChange();
    mBoss.superStop().unsetAutoSpecial();
    mBoss.custom()->onStateChange();
}

void StateCallback::setCanClearAttack(bool canClearAttack) {
    mCanClearAttack = canClearAttack;
}

}}}  // namespace scn::step::boss
