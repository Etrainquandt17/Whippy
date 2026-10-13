#include "scn/step/boss/common/StateMoveBack.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "gobj/Target.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateMoveBack::StateMoveBack(Boss* boss, StateMoveDesc desc, unsigned long scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
    obj().brainCtrl().toValid();
}

StateMoveBack::~StateMoveBack() {}

void StateMoveBack::procAnim() {}

void StateMoveBack::procMove() {
    obj().move().groundAccel(!obj().target().isRightDir(), mDesc._0);
}

void StateMoveBack::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::common
