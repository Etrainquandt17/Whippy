#include "scn/step/enemy/watergalbo/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/watergalbo/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace watergalbo {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.WaterGalbo.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}
}
}
}
