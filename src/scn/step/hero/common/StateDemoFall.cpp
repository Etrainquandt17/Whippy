#include "scn/step/hero/common/StateDemoFall.h"
#include "gobj/Move.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Flash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StatePlancher.h"
#include "scn/step/hero/common/StatePlancherLanding.h"
#include "scn/step/hero/common/StateWait.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateDemoFall::StateDemoFall(Hero* hero)
    : StateBase(hero)
    , mFrame(hero->param().common()._228) {
    switch (obj().model().anim().currentG3DAnimIndex()) {
    case 0x33:
    case 0x34:
        obj().model().script().start(0x37);
        mFrame = 0;
        break;
    default:
        obj().model().script().start(2);
        break;
    }
    obj().objColl().setXlu();
    obj().flash().setValid(false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    Utility::SetSecondMoveIsValid(obj(), false);
    Utility::CloseGearParasol(obj());
}

StateDemoFall::~StateDemoFall() {
    Utility::SetSecondMoveIsValid(obj(), true);
    obj().stateChecker().setIsForbidSpaceJump(false);
    obj().flash().setValid(true);
    obj().objColl().unsetXlu();
}

void StateDemoFall::procAnim() {
    if (mFrame != 0) {
        mFrame--;
        if (canPlancher()) {
            obj().model().script().start(0x36);
            obj().stateChecker().setPlancher(true);
        }
    }
}

void StateDemoFall::procMove() {
    gobj::MoveParamFall fall = obj().param().common()._90;
    fall._0 = 0.3f;
    obj().move().airDecelFall(obj().param().common()._74, fall);
}

void StateDemoFall::procFixPos() {
    if (canPlancher()) {
        if (StatePlancherLanding::TryToChangeState(objPtr())) {
            return;
        }
    } else if (StateWait::TryToChangeStateWithScript(objPtr(), SCRIPT_KIND_3)) {
        return;
    }
}

bool StateDemoFall::canPlancher() {
    if (StatePlancher::CanPlancher(objPtr())) {
        return mFrame == 0;
    }
    return false;
}

}
}
}
}
