#include "scn/step/enemy/broomhatter/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/broomhatter/StateGrandLowperEscapeStart.h"
#include "scn/step/enemy/broomhatter/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BroomHatter.SetNextState", "void Walk()", Walk, SetNextState<StateWalk>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.BroomHatter.SetNextState", "void GrandLowperEscape()", GrandLowperEscape, SetNextState<StateGrandLowperEscapeStart>);
}

}

}}}}  // namespace scn::step::enemy::broomhatter
