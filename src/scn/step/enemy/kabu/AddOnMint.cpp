#include "scn/step/enemy/kabu/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/kabu/Custom.h"
#include "scn/step/enemy/kabu/StateGrandLowperEscapeStart.h"
#include "scn/step/enemy/kabu/StateJump.h"
#include "scn/step/enemy/kabu/StateMove.h"
#include "scn/step/enemy/kabu/StateMoveAround.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

namespace {

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Move() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMove, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveAround() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveAround, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_GrandLowperEscape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGrandLowperEscapeStart, Enemy*>(MintEnemy::Obj());
}

int t_Custom_setJumpWaitTime() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setJumpWaitTime();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Kabu.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Kabu.SetNextState", "void Move()", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Kabu.SetNextState", "void MoveAround()", MoveAround, t_SetNextState_MoveAround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Kabu.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, t_SetNextState_GrandLowperEscape);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Kabu.Custom", "int setJumpWaitTime()", setJumpWaitTime, t_Custom_setJumpWaitTime);
}

}

}}}}  // namespace scn::step::enemy::kabu
