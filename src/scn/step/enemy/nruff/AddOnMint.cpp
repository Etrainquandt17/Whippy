#include "scn/step/enemy/nruff/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "mintglue/WrapNative.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/nruff/StateGrandLowperEscapeStart.h"
#include "scn/step/enemy/nruff/StateStay.h"
#include "scn/step/enemy/nruff/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

namespace {

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Stay() {
    MintEnemy::Obj()->stateChanger().setNextState<StateStay, Enemy*>(MintEnemy::Obj());
}

void t_Model_ReqScriptWalk() {
    MintEnemy::Obj()->model().reqScript(3);
}

void t_SetNextState_GrandLowperEscape() {
    MintEnemy::Obj()->stateChanger().setNextState<StateGrandLowperEscapeStart, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Nruff.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Nruff.SetNextState", "void Stay()", Stay, t_SetNextState_Stay);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Nruff.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, t_SetNextState_GrandLowperEscape);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Nruff.Model", "void ReqScriptWalk()", ReqScriptWalk, t_Model_ReqScriptWalk);
}

}

}}}}  // namespace scn::step::enemy::nruff
