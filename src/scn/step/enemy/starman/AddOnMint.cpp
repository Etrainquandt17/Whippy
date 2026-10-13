#include "scn/step/enemy/starman/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/starman/StateFly.h"
#include "scn/step/enemy/starman/StateJumpStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

namespace {

void t_SetNextState_JumpStart() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJumpStart, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFly, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Starman.SetNextState", "void JumpStart()", JumpStart, t_SetNextState_JumpStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Starman.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
}

}

}
}
}
}
