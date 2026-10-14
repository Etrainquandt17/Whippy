#include "scn/step/boss/doubter/StateWait.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/HateCtrl.h"
#include "scn/step/boss/MapColl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/doubter/BodyCollCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/Param.h"
#include "scn/step/chara/MapCollResult.h"
#include "scn/step/chara/Model.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace boss {
namespace doubter {

StateWait::StateWait(Boss* boss) : StateBase(boss) {
    DynamicCastToRef<Custom, ICustom>(obj().custom()).bodyCollCtrl().setState(BodyCollCtrl::STATE_2);
    obj().model().reqScript(0);
    obj().brainCtrl().toValid();
    obj().hateCtrl().fix();
}

StateWait::~StateWait() {}

void StateWait::procAnim() {
    Utility::TurnHatedHero(obj());
}

void StateWait::procMove() {
    if (obj().footState().isGround()) {
        obj().move().groundDecel(obj().param().doubter()._10);
    } else {
        obj().move().airDecelFall(obj().param().doubter()._10, obj().param().doubter()._18);
    }
}

void StateWait::procFixPos() {
    chara::MapCollResult result = obj().mapColl().result();
    if (result.mIsHitFloor) {
        obj().move().resetSpeedV();
        obj().footState().setGround();
    }
}

}}}}  // namespace scn::step::boss::doubter
