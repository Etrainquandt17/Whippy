#include "scn/step/boss/bonkers/StateBombStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/bonkers/Param.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

StateBombStart::StateBombStart(Boss* boss) : StateBase(boss) {
    obj().footState().setGround();
    obj().model().reqScript(13);
}

StateBombStart::~StateBombStart() {}

void StateBombStart::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
    }
}

void StateBombStart::procMove() {
    obj().move().groundDecel(obj().param().bonkers()._24);
}

void StateBombStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::bonkers
