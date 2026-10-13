#include "scn/step/enemy/galbo/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/galbo/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace galbo {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Galbo.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}}}}  // namespace scn::step::enemy::galbo
