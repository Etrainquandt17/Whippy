#include "scn/step/enemy/squishy/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/squishy/Custom.h"
#include "scn/step/enemy/squishy/StateJump.h"
#include "scn/step/enemy/squishy/StateMoveInWater.h"
#include "scn/step/enemy/squishy/StateMoveOnLand.h"
#include "scn/step/enemy/squishy/StateSwim.h"
#include "scn/step/enemy/squishy/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

namespace {

void t_SetNextState_Swim() {
    MintEnemy::Obj()->stateChanger().setNextState<StateSwim, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveInWater() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveInWater, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveOnLand() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveOnLand, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsJumpFromWater() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isJumpFromWater();
}

bool t_Custom_IsInWater(bool flag) {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isInWater(flag);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.SetNextState", "void Swim()", Swim, t_SetNextState_Swim);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.SetNextState", "void MoveInWater()", MoveInWater, t_SetNextState_MoveInWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.SetNextState", "void MoveOnLand()", MoveOnLand, t_SetNextState_MoveOnLand);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.Custom", "bool IsJumpFromWater()", IsJumpFromWater, t_Custom_IsJumpFromWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Squishy.Custom", "bool IsInWater(bool)", IsInWater, t_Custom_IsInWater);
}

}

}}}}  // namespace scn::step::enemy::squishy
