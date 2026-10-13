#include "scn/step/enemy/whippy/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/whippy/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Whippy.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}
}
}
}
