#include "scn/step/hero/common/StateClearDanceFall.h"
#include "scn/step/Component.h"
#include "scn/step/hero/ClearDanceUtil.h"
#include "scn/step/hero/Flash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateClearDanceWalk.h"
#include "scn/step/vacuum/Attacker.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateClearDanceFall::StateClearDanceFall(Hero* hero)
    : StateBase(hero)
    , mZoom(0) {
    Utility::ReleaseCarryItem(obj());
    obj().objColl().setXlu();
    obj().flash().setValid(false);
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().vacuumAttacker().resetVacuumCount();
    obj().vacuumAttacker().resetVacuumHold();
    if (obj().isMainPlayer()) {
        obj().comp().heroManager().setHidDisable();
    }
    obj().model().script().start(2);
    mZoom = ClearDanceUtil::SetZoom(obj());
    obj().comp().heroManager().cureAll();
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().setCanCatchItem(false);
    obj().setCanReactGimmick(false);
}

StateClearDanceFall::~StateClearDanceFall() {
    Utility::SetSecondMoveIsValid(obj(), true);
    obj().flash().setValid(true);
    obj().objColl().unsetXlu();
}

void StateClearDanceFall::procAnim() {
    mZoom = ClearDanceUtil::ResetZoom(obj(), mZoom);
}

void StateClearDanceFall::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateClearDanceFall::procFixPos() {
    MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().stateChanger().setNextState<StateClearDanceWalk, Hero*, u32>(objPtr(), mZoom);
    }
}

}}}}  // namespace scn::step::hero::common
