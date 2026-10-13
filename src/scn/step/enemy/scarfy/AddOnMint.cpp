#include "scn/step/enemy/scarfy/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/scarfy/Custom.h"
#include "scn/step/enemy/scarfy/StateEscape.h"

namespace scn {
namespace step {
namespace enemy {
namespace scarfy {

namespace {

bool t_IsAnger() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isAngerFlag();
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Scarfy.SetNextState", "void Escape()", Escape, SetNextState<StateEscape>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Scarfy.Custom", "bool IsAnger()", IsAnger, t_IsAnger);
}

}

}
}
}
}
