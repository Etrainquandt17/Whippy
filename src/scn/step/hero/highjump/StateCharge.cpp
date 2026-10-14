#include "scn/step/hero/highjump/StateCharge.h"
#include "scn/step/hero/ButtonMask.h"
#include "scn/step/hero/ChargeFlash.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/highjump/StateJump.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace highjump {

bool StateCharge::tryToChangeState(Hero* hero) {
    u32 frame = hero->commandManager().getHoldFrame(static_cast<ButtonMask>(0x20));
    if (frame != 0 && frame < 0x14) {
        hero->stateChanger().setNextState<StateCharge, Hero*>(hero);
        return true;
    }
    return false;
}

StateCharge::StateCharge(Hero* hero)
    : StateBase(hero)
    , mFrame(0)
    , mKind(JUMP_KIND_0) {
    Utility::AirAttackInitSpeedV(obj());
    obj().piggyback().setEnableReceive(true);
    obj().model().setSELoopNoReset();
    obj().model().script().start(0xF4);
}

StateCharge::~StateCharge() {
    obj().chargeFlash().clear();
}

void StateCharge::procAnim() {
    mFrame++;
    if (obj().model().scriptTrigger().get(0)) {
        mKind = JUMP_KIND_1;
        obj().chargeFlash().set(ChargeFlash::CHARGE_LV_1);
    }
    if (obj().model().scriptTrigger().get(1)) {
        mKind = JUMP_KIND_2;
        obj().chargeFlash().set(ChargeFlash::CHARGE_LV_3);
    }
    if (!obj().hid().isHold(0x20)) {
        obj().stateChanger().setNextState<StateJump, Hero*, JumpKind>(objPtr(), mKind);
    }
}

void StateCharge::procMove() {
    Utility::MoveDefaultAction(obj());
}

void StateCharge::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}}}}  // namespace scn::step::hero::highjump
