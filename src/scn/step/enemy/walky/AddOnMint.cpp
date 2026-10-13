#include "scn/step/enemy/walky/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/walky/StateAttackStart.h"
#include "scn/step/enemy/walky/StateJump.h"
#include "scn/step/enemy/walky/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace walky {

namespace {

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_AttackStart() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttackStart, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walky.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walky.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walky.SetNextState", "void AttackStart()", AttackStart, t_SetNextState_AttackStart);
}

}

}}}}  // namespace scn::step::enemy::walky
