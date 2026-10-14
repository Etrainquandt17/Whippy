#include "scn/step/enemy/tick/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Effect.h"
#include "scn/step/enemy/Effect.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/tick/StateAttack.h"
#include "scn/step/enemy/tick/StateSkip.h"

namespace scn {
namespace step {
namespace enemy {
namespace tick {

namespace {

void t_Custom_AttackEffect() {
    MintEnemy::Obj()->effect().state().requestN(static_cast<effect::Kind>(0x492), 0);
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tick.SetNextState", "void Skip()", Skip, SetNextState<StateSkip>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tick.SetNextState", "void Attack()", Attack, SetNextState<StateAttack>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tick.SetNextState", "void Wait()", Wait, SetNextState<common::StateWait>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tick.Custom", "void AttackEffect()", AttackEffect, t_Custom_AttackEffect);
}

}

}}}}  // namespace scn::step::enemy::tick
