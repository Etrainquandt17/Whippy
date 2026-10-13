#include "scn/step/hero/common/StateClearDancePre.h"
#include "gobj/FootState.h"
#include "scn/step/Component.h"
#include "scn/step/hero/ClearDanceUtil.h"
#include "scn/step/hero/Flash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/IndiviUtil.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/WearBack.h"
#include "scn/step/hero/common/StateClearDance.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateClearDancePre::StateClearDancePre(Hero* hero, u32 zoom)
    : StateBase(hero)
    , mFrame(0)
    , mZoom(zoom) {
    obj().stateChecker().setDemo(true);
    obj().footState().setGround();
    obj().model().script().start(0x27);
    obj().objColl().setXlu();
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().flash().setValid(false);
    if (IndiviUtil::IsKirby(obj().kind())) {
        obj().wearBack().setBack();
    }
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().setCanCatchItem(false);
    obj().setCanReactGimmick(false);
    mZoom = ClearDanceUtil::ResetZoom(obj(), mZoom);
}

StateClearDancePre::~StateClearDancePre() {}

void StateClearDancePre::procAnim() {
    mFrame++;
    mZoom = ClearDanceUtil::ResetZoom(obj(), mZoom);
    if (mFrame == 120) {
        obj().stateChecker().set_40(true);
    }
    if (mFrame == 1200) {
        obj().comp().heroManager().setClearDanceReadyAllForce();
    }
    if (obj().comp().heroManager().isClearDanceReadyAll()) {
        obj().stateChanger().setNextState<StateClearDance, Hero*>(objPtr());
    }
}

void StateClearDancePre::procMove() {
    Utility::MoveDefaultBrake(obj());
}

void StateClearDancePre::procFixPos() {}

}}}}  // namespace scn::step::hero::common
