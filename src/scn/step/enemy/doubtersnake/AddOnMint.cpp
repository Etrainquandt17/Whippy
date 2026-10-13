#include "scn/step/enemy/doubtersnake/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/doubtersnake/StateEscapeNear.h"
#include "scn/step/enemy/doubtersnake/StateJump.h"
#include "scn/step/enemy/doubtersnake/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

namespace {

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_EscapeNear() {
    MintEnemy::Obj()->stateChanger().setNextState<StateEscapeNear, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DoubterSnake.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DoubterSnake.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DoubterSnake.SetNextState", "void EscapeNear()", EscapeNear, t_SetNextState_EscapeNear);
}

}

}}}}  // namespace scn::step::enemy::doubtersnake
