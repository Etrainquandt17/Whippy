#include "scn/step/boss/moundeath/StatePressJumpStart.h"

#include "gobj/FootState.h"
#include "gobj/Move.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/StateBase.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateFall.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/StatePressJump.h"
#include "scn/step/boss/moundeath/States.h"
#include "scn/step/chara/Model.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

StatePressJumpStart::StatePressJumpStart(Boss* boss, JumpKind kind) : StateBase(boss), mKind(kind) {
    obj().footState().setGround();
    switch (mKind) {
    case JUMP_KIND_0:
    case JUMP_KIND_1:
    case JUMP_KIND_2:
        obj().model().reqScript(9);
        break;
    case JUMP_KIND_3:
        obj().model().reqScript(0x12);
        break;
    }
    Utility::ControlHateOnAction(obj());
}

StatePressJumpStart::~StatePressJumpStart() {}

void StatePressJumpStart::procAnim() {
    if (obj().model().isAllEnd()) {
        switch (mKind) {
        case JUMP_KIND_0:
        case JUMP_KIND_1:
        case JUMP_KIND_2:
            obj().stateChanger().setNextState<StatePressJump, Boss*, JumpKind>(objPtr(), mKind);
            break;
        case JUMP_KIND_3: {
            StateRollJump::Config config;
            config._0 = true;
            obj().stateChanger().setNextState<StateRollJump, Boss*, StateRollJump::Config>(objPtr(), config);
            break;
        }
        }
    }
}

void StatePressJumpStart::procMove() {
    const Param& param = obj().param().moundeath();
    obj().move().groundDecel(param._24);
}

void StatePressJumpStart::procFixPos() {
    common::StateFall::TryToChangeState(objPtr());
}

}}}}  // namespace scn::step::boss::moundeath
