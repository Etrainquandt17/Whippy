#include "scn/step/enemy/waddledoo/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/waddledoo/StateAttack.h"
#include "scn/step/enemy/waddledoo/StateJump.h"

namespace scn {
namespace step {
namespace enemy {
namespace waddledoo {

namespace {

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.WaddleDoo.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.WaddleDoo.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}}}}  // namespace scn::step::enemy::waddledoo
