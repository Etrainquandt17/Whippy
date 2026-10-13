#include "scn/step/enemy/bladeknight/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/bladeknight/StateAttack.h"
#include "scn/step/enemy/bladeknight/StateDoubleAttack.h"
#include "scn/step/enemy/bladeknight/StateGrandLowperEscapeStart.h"
#include "scn/step/enemy/bladeknight/StateStepBack.h"
#include "scn/step/enemy/bladeknight/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace bladeknight {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_DoubleAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDoubleAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_StepBack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateStepBack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_GrandLowperEscape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGrandLowperEscapeStart, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BladeKnight.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BladeKnight.SetNextState", "void DoubleAttack()", DoubleAttack, t_SetNextState_DoubleAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BladeKnight.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BladeKnight.SetNextState", "void StepBack()", StepBack, t_SetNextState_StepBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BladeKnight.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, t_SetNextState_GrandLowperEscape);
}

}

}
}
}
}
