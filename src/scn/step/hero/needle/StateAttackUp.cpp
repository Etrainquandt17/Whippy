#include "scn/step/hero/needle/StateAttackUp.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/chara/ObjColl.h"
#include "scn/step/chara/Shake.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Invincible.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/NeedleParam.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/ScriptKind.h"
#include "scn/step/hero/SoundSE.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/needle/StateAttackUpEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace needle {

namespace {

inline const NeedleParamAttackUp& param(Hero& hero) {
    return hero.param().needle()._30;
}

}

bool StateAttackUp::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(8) && hero->hid().isTrigger(0x20)) {
        hero->stateChanger().setNextState<StateAttackUp, Hero*>(hero);
        return true;
    }
    return false;
}

StateAttackUp::StateAttackUp(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mIsAir(false) {
    obj().piggyback().unlinkAll();
    obj().model().setFixDir(true);
    obj().model().script().start(0xBA);
    Utility::AirAttackInitSpeedV(obj());
    const NeedleParamAttackUp& p = param(obj());
    obj().invincible().set(p._0);
}

StateAttackUp::~StateAttackUp() {
}

void StateAttackUp::procAnim() {
    mFrame++;
    if (mFrame > param(obj())._4) {
        obj().stateChanger().setNextState<StateAttackUpEnd, Hero*>(objPtr());
    }
}

void StateAttackUp::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateAttackUp::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
    if (mIsAir && obj().footState().isGround()) {
        obj().soundSE()._4.start(0x1A9);
    }
    mIsAir = obj().footState().isAir();
}

bool StateAttackUp::procObjCollReact() {
    if (obj().objColl().objColl().isAttackCollide()) {
        obj().model().shake().request(static_cast<chara::ShakeKind>(3));
    }
    return false;
}

}}}}  // namespace scn::step::hero::needle
