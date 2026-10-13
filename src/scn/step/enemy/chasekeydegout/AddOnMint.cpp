#include "scn/step/enemy/chasekeydegout/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/chasekeydegout/StateChase.h"

namespace scn {
namespace step {
namespace enemy {
namespace chasekeydegout {

namespace {

void t_SetNextState_Chase() {
    MintEnemy::Obj()->stateChanger().setNextState<StateChase, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.ChaseKeyDegout.SetNextState", "void Chase()", Chase, t_SetNextState_Chase);
}

}

}}}}  // namespace scn::step::enemy::chasekeydegout
