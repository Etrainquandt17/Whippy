#include "scn/step/enemy/blipper/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/blipper/StateChase.h"
#include "scn/step/enemy/blipper/StateDive.h"
#include "scn/step/enemy/blipper/StateFall.h"
#include "scn/step/enemy/blipper/StateFattyBufferEscapeNear.h"
#include "scn/step/enemy/blipper/StateFlyingOut.h"
#include "scn/step/enemy/blipper/StateJump.h"
#include "scn/step/enemy/blipper/StateLanding.h"
#include "scn/step/enemy/blipper/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

namespace {

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Chase()", Chase, SetNextState<StateChase>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Dive()", Dive, SetNextState<StateDive>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Fall()", Fall, SetNextState<StateFall>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void FlyingOut()", FlyingOut, SetNextState<StateFlyingOut>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Jump()", Jump, SetNextState<StateJump>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Landing()", Landing, SetNextState<StateLanding>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void Move()", Move, SetNextState<StateMove>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Blipper.SetNextState", "void FattyBufferEscapeNear()", FattyBufferEscapeNear, SetNextState<StateFattyBufferEscapeNear>);
}

}

}}}}  // namespace scn::step::enemy::blipper
