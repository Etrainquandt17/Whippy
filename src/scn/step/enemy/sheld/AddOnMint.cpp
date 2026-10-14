#include "scn/step/enemy/sheld/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/sheld/StateChase.h"
#include "scn/step/enemy/sheld/StateDash.h"
#include "scn/step/enemy/sheld/StateEscape.h"
#include "scn/step/enemy/sheld/StateGrandLowperEscapeStart.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

namespace {

void t_SetNextState_Dash() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDash, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Chase() {
    MintEnemy::Obj()->stateChanger().setNextState<StateChase, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Escape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateEscape, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_GrandLowperEscape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGrandLowperEscapeStart, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sheld.SetNextState", "void Dash()", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sheld.SetNextState", "void Chase()", Chase, t_SetNextState_Chase);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sheld.SetNextState", "void Escape()", Escape, t_SetNextState_Escape);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Sheld.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, t_SetNextState_GrandLowperEscape);
}

}

}}}}  // namespace scn::step::enemy::sheld
