#include "scn/step/enemy/lupa/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/lupa/Custom.h"
#include "scn/step/enemy/lupa/StateMoveAroundAttack.h"
#include "scn/step/enemy/lupa/StateWait.h"
#include "scn/step/enemy/lupa/StateWaitAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

namespace {

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WaitAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWaitAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveAroundAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveAroundAttack, Enemy*>(MintEnemy::Obj());
}

// The game has no state of this name: the binding starts the same one as MoveAroundAttack.
void t_SetNextState_MoveTurnCliffAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveAroundAttack, Enemy*>(MintEnemy::Obj());
}

bool t_SetNextState_CheckExistLand() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).checkExistLand();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lupa.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lupa.SetNextState", "void WaitAttack()", WaitAttack, t_SetNextState_WaitAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lupa.SetNextState", "void MoveAroundAttack()", MoveAroundAttack, t_SetNextState_MoveAroundAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lupa.SetNextState", "void MoveTurnCliffAttack()", MoveTurnCliffAttack, t_SetNextState_MoveTurnCliffAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Lupa.Custom", "bool CheckExistLand()", CheckExistLand, t_SetNextState_CheckExistLand);
}

}

}}}}  // namespace scn::step::enemy::lupa
