#include "scn/step/boss/common/StateDashEnd.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/common/StateWait.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace common {

StateDashEnd::StateDashEnd(Boss* boss, StateDashDesc& desc, unsigned long scriptKind) : StateBase(boss), mDesc(desc) {
    obj().footState().setGround();
    obj().model().reqScript(scriptKind);
}

StateDashEnd::~StateDashEnd() {}

void StateDashEnd::procAnim() {
    if (obj().model().isAllEnd()) {
        obj().stateChanger().setNextState<StateWait, Boss*>(objPtr());
    }
}

void StateDashEnd::procMove() {
    obj().move().groundDecel(mDesc._10);
}

void StateDashEnd::procFixPos() {
    StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::common
