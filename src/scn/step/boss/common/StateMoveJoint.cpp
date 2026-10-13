#include "scn/step/boss/common/StateMoveJoint.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/BrainCtrl.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateMoveJoint::StateMoveJoint(Boss* boss, StateMoveJointDesc desc, u32 scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
}

StateMoveJoint::~StateMoveJoint() {}

void StateMoveJoint::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().brainCtrl().toValid();
        obj().model().reqScript(0);
    }
}

void StateMoveJoint::procMove() {
    obj().move().groundDecel(mDesc._0);
}

void StateMoveJoint::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::common
