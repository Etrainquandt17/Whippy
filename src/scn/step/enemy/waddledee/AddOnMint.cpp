#include "scn/step/enemy/waddledee/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/waddledee/StateGrandLowperEscapeStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

namespace {

void t_SetNextState_GrandLowperEscape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGrandLowperEscapeStart, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.WaddleDee.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, t_SetNextState_GrandLowperEscape);
}

}

}
}
}
}
