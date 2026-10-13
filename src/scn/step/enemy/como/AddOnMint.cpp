#include "scn/step/enemy/como/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/como/StateDive.h"

namespace scn {
namespace step {
namespace enemy {
namespace como {

namespace {

void t_SetNextState_Dive() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDive, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Como.SetNextState", "void Dive()", Dive, t_SetNextState_Dive);
}

}

}}}}  // namespace scn::step::enemy::como
