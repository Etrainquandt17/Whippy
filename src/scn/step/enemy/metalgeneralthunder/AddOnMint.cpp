#include "scn/step/enemy/metalgeneralthunder/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/metalgeneralthunder/StateAttack.h"
#include "scn/step/enemy/metalgeneralthunder/StateDead.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Dead() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDead, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MetalGeneralThunder.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MetalGeneralThunder.SetNextState", "void Dead()", Dead, t_SetNextState_Dead);
}

}

}
}
}
}
