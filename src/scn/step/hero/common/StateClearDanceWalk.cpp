#include "scn/step/hero/common/StateClearDanceWalk.h"
#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "hel/math/Math.h"
#include "scn/step/Component.h"
#include "scn/step/chara/Location.h"
#include "scn/step/hero/ClearDanceUtil.h"
#include "scn/step/hero/CommonParam.h"
#include "scn/step/hero/Flash.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MapColl.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/Nururi.h"
#include "scn/step/hero/ObjColl.h"
#include "scn/step/hero/Param.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/Utility.h"
#include "scn/step/hero/common/StateClearDancePre.h"
#include "util/StateChanger.h"

namespace scn {
namespace step {
namespace hero {
namespace common {

StateClearDanceWalk::StateClearDanceWalk(Hero* hero, u32 zoom)
    : StateBase(hero)
    , mTargetPos(hero->comp().heroManager().getClearDancePos(hero->padChan()))
    , mZoom(zoom) {
    obj().stateChecker().setDemo(true);
    obj().footState().setGround();
    obj().model().script().start(4);
    obj().objColl().setXlu();
    Utility::SetSecondMoveIsValid(obj(), false);
    obj().move().resetVelocity();
    obj().flash().setValid(false);
    obj().nururi().setValid(false);
    obj().nururi().setCanNururi(false);
    obj().mapColl().setValid(false);
    obj().stateChecker().setIsForbidSpaceJump(true);
    obj().setCanCatchItem(false);
    obj().setCanReactGimmick(false);
    mZoom = ClearDanceUtil::ResetZoom(obj(), mZoom);
}

StateClearDanceWalk::~StateClearDanceWalk() {}

void StateClearDanceWalk::procAnim() {
    mZoom = ClearDanceUtil::ResetZoom(obj(), mZoom);
}

void StateClearDanceWalk::procMove() {
    obj().target().setIsRightDir(obj().location().pos().x < mTargetPos.x);
    obj().move().groundAccel(obj().target().isRightDir(), obj().param().common()._254);
    hel::math::Vector3 pos = obj().location().pos();
    pos.z = 0.9f * pos.z + 0.1f * mTargetPos.z;
    obj().location().setPos(pos);
}

void StateClearDanceWalk::procFixPos() {
    if (hel::math::Math::AbsF32(obj().location().pos().x - mTargetPos.x) < 0.2f) {
        obj().location().setPos(hel::math::Vector3(mTargetPos.x, obj().location().pos().y, mTargetPos.z));
        obj().stateChanger().setNextState<StateClearDancePre, Hero*, u32>(objPtr(), mZoom);
    }
}

}
}
}
}
