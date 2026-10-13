#include "scn/step/enemy/chilly/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/chilly/StateAttack.h"
#include "scn/step/enemy/chilly/StateLookAround.h"
#include "scn/step/enemy/chilly/StateMove.h"
#include "scn/step/enemy/common/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Chilly.SetNextState", "void Wait()", Wait, SetNextState<common::StateWait>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Chilly.SetNextState", "void Move()", Move, SetNextState<StateMove>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Chilly.SetNextState", "void LookAround()", LookAround, SetNextState<StateLookAround>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Chilly.SetNextState", "void Attack()", Attack, SetNextState<StateAttack>);
}

}

}}}}  // namespace scn::step::enemy::chilly
