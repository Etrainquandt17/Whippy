#include "scn/step/enemy/common/AddOnMint.h"

#include "app/Application.h"
// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "hel/math/Random.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateFall.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/common/StateMahoroa1Disappear.h"
#include "scn/step/enemy/common/StateWait.h"
#include "scn/step/enemy/common/StateWalkAround.h"
#include "scn/step/enemy/common/StateWalkStraight.h"

using app::Application;
using hel::common::ExplicitSingleton;

namespace scn {
namespace step {
namespace enemy {
namespace common {

namespace {

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WalkStraight() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkStraight, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WalkAround() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWalkAround, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Fall() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFall, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Mahoroa1Disappear() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMahoroa1Disappear, Enemy*>(MintEnemy::Obj());
}

int t_Random_Rand(int max) {
    return ExplicitSingleton<Application>::object_->random().rand(max);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void WalkStraight()", WalkStraight, t_SetNextState_WalkStraight);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void WalkAround()", WalkAround, t_SetNextState_WalkAround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void Fall()", Fall, t_SetNextState_Fall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common.SetNextState", "void Mahoroa1Disappear()", Mahoroa1Disappear, t_SetNextState_Mahoroa1Disappear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Common", "int Random_Rand(int)", Random_Rand, t_Random_Rand);
}

}

}}}}  // namespace scn::step::enemy::common
