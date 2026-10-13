#include "scn/step/hero/crash/StateCharge.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Script.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/CrashParam.h"
#include "scn/step/hero/Effect.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/LandAttribute.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ShakeCharge.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/crash/StateAttack.h"
#include "scn/step/hero/crash/Utility.h"
#include "scn/step/sfx/SuperFade.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace crash {

bool StateCharge::TryToChangeState(Hero* hero) {
    if (hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateCharge, Hero*>(hero);
        return true;
    }
    return false;
}

StateCharge::StateCharge(Hero* hero)
    : StateBase(hero)
    , mIsCharged(false)
    , mIsAttack(false) {
    hero::Utility::AirAttackInitSpeedV(obj());
    obj().comp().superFade().setValid(true);
    Utility::RequestHatEffectAttack(obj());
    ShakeChargeEnv env = obj().param().crash()._14;
    obj().shakeCharge().setEnv(env._0, env._4, env._8, env._C);
    obj().shakeCharge().reset();
    obj().model().script().start(0x184);
    obj().piggyback().unlinkAll();
}

StateCharge::~StateCharge() {
    Utility::RequestHatEffectNormal(obj());
    obj().comp().superFade().setValid(false);
    if (!mIsAttack) {
        obj().effect()._58.releaseAndVanish();
    }
    obj().shakeCharge().reset();
}

void StateCharge::procAnim() {
    chkCharge();
    if (StateAttack::TryToChangeState(objPtr(), mIsCharged)) {
        mIsAttack = true;
    }
}

void StateCharge::procMove() {
    const CrashParam& param = obj().param().crash();
    if (obj().footState().isAir()) {
        obj().move().airDecelFall(param._4, param._8);
    } else {
        obj().move().groundDecel(param._0);
    }
}

void StateCharge::procFixPos() {
    bool isAir = obj().footState().isAir();
    hero::Utility::MapCollReactDefaultAction(obj());
    if (isAir && obj().footState().isGround()) {
        obj().landAttribute().reqEffectLanding(0.0f, 0.1f);
        obj().soundSE()._4.start(0x113);
    }
}

void StateCharge::chkCharge() {
    if (mIsCharged) {
        return;
    }
    u32 frame = obj().commandManager().getTriggerPastFrame(static_cast<ButtonMask>(0x20));
    mIsCharged = isShakeMax() && frame > 60;
    if (mIsCharged) {
        changeMotion();
    }
}

void StateCharge::changeMotion() {
    obj().model().script().start(0x185);
}

bool StateCharge::isShakeMax() {
    return obj().shakeCharge().power() >= obj().param().crash()._14._8;
}

}}}}  // namespace scn::step::hero::crash
