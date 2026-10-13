#include "scn/step/hero/leaf/StateHide.h"
#include "gobj/FootState.h"
#include "gobj/Script.h"
#include "scn/step/hero/CommandManager.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Hid.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/Piggyback.h"
#include "scn/step/hero/PowerCharge.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/interference/StateSpaceJump.h"
#include "scn/step/hero/leaf/StateHideEnd.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

bool StateHide::TryToChangeState(Hero* hero) {
    if (hero->hid().isHold(0x40) && hero->footState().isGround()) {
        hero->stateChanger().setNextState<StateHide, Hero*>(hero);
        return true;
    }
    return false;
}

StateHide::StateHide(Hero* hero)
    : StateBase(hero) {
    obj().model().script().start(0x9A);
    obj().objColl().setXlu();
    obj().commandManager().resetHoldFrame(static_cast<ButtonMask>(0x200));
    obj().powerCharge().setCanCharge(true);
    obj().piggyback().setEnableReceive(true);
    obj().stateChecker().set_59(true);
}

StateHide::~StateHide() {
    obj().objColl().unsetXlu();
}

void StateHide::procAnim() {
    if (!obj().isMainPlayer() && obj().hid().isHold(0x200) &&
        obj().commandManager().getHoldFrame(static_cast<ButtonMask>(0x200)) >= obj().param().common()._3AC) {
        obj().stateChanger().setNextState<interference::StateSpaceJump, Hero*, interference::StateSpaceJump::NextState>(
            objPtr(), interference::StateSpaceJump::NEXT_STATE_0);
        return;
    }
    if (!obj().hid().isHold(0x40) || obj().footState().isAir()) {
        obj().stateChanger().setNextState<StateHideEnd, Hero*>(objPtr());
    }
}

void StateHide::procMove() {
    Utility::MoveGuard(obj());
}

void StateHide::procFixPos() {
    Utility::MapCollReactDefaultAction(obj());
}

}
}
}
}
