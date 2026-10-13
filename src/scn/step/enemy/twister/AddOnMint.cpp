#include "scn/step/enemy/twister/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/twister/StateChase.h"
#include "scn/step/enemy/twister/StateRise.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

namespace {

void t_SetNextState_Rise() {
    MintEnemy::Obj()->stateChanger().setNextState<StateRise, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Chase() {
    MintEnemy::Obj()->stateChanger().setNextState<StateChase, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Twister.SetNextState", "void Rise()", Rise, t_SetNextState_Rise);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Twister.SetNextState", "void Chase()", Chase, t_SetNextState_Chase);
}

}

}
}
}
}
