#include "scn/step/enemy/metalgeneralbit/AddOnMint.h"

#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/metalgeneralbit/StateDead.h"
#include "scn/step/enemy/metalgeneralbit/StateMove.h"
#include "scn/step/enemy/metalgeneralbit/StateShot.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

namespace {

void t_SetNextState_Move() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMove, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Shot() {
    MintEnemy::Obj()->stateChanger().setNextState<StateShot, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Dead() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDead, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MetalGeneralBit.SetNextState", "void Move()", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MetalGeneralBit.SetNextState", "void Shot()", Shot, t_SetNextState_Shot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.MetalGeneralBit.SetNextState", "void Dead()", Dead, t_SetNextState_Dead);
}

}

}}}}  // namespace scn::step::enemy::metalgeneralbit
