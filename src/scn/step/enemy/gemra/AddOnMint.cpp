#include "scn/step/enemy/gemra/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/gemra/StateAttack.h"
#include "scn/step/enemy/gemra/StateFly.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

namespace {

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gemra.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gemra.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}
}
}
}
