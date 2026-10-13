#include "scn/step/enemy/pacto/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/pacto/StateDive.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

namespace {

void t_SetNextState_Dive() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDive, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Pacto.SetNextState", "void Dive()", Dive, t_SetNextState_Dive);
}

}

}
}
}
}
