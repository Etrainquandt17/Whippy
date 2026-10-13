#include "scn/step/enemy/noddy/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/noddy/StateWalk.h"

namespace scn {
namespace step {
namespace enemy {
namespace noddy {

namespace {

void t_SetNextState_Walk() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalk, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Noddy.SetNextState", "void Walk()", Walk, t_SetNextState_Walk);
}

}

}}}}  // namespace scn::step::enemy::noddy
