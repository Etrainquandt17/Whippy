#include "scn/step/enemy/bulby/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/bulby/StateAttack.h"
#include "scn/step/enemy/bulby/StateHide.h"
#include "scn/step/enemy/bulby/StateJump.h"
#include "scn/step/enemy/bulby/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace bulby {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bulby.SetNextState", "void Wait()", Wait, SetNextState<StateWait>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bulby.SetNextState", "void Jump()", Jump, SetNextState<StateJump>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bulby.SetNextState", "void Attack()", Attack, SetNextState<StateAttack>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bulby.SetNextState", "void Hide()", Hide, SetNextState<StateHide>);
}

}

}
}
}
}
