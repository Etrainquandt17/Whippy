#include "scn/step/enemy/rocky/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/rocky/StateStay.h"
#include "scn/step/enemy/rocky/StateWalkStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

namespace {

void t_SetNextState_WalkStart() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkStart, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Stay() {
    MintEnemy::Obj()->stateChanger().setNextState<StateStay, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Rocky.SetNextState", "void WalkStart()", WalkStart, t_SetNextState_WalkStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Rocky.SetNextState", "void Stay()", Stay, t_SetNextState_Stay);
}

}

}}}}  // namespace scn::step::enemy::rocky
