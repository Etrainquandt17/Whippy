#include "scn/step/enemy/walf/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/walf/Custom.h"
#include "scn/step/enemy/walf/StateMoveInWater.h"
#include "scn/step/enemy/walf/StateMoveOnGround.h"
#include "scn/step/enemy/walf/StateMoveOnWater.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

namespace {

void t_SetNextState_MoveInWater() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveInWater, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveOnGround() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveOnGround, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_MoveOnWater() {
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveOnWater, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsInWater() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isInWater();
}

bool t_Custom_IsFloating() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isFloating();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walf.SetNextState", "void MoveInWater()", MoveInWater, t_SetNextState_MoveInWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walf.SetNextState", "void MoveOnGround()", MoveOnGround, t_SetNextState_MoveOnGround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walf.SetNextState", "void MoveOnWater()", MoveOnWater, t_SetNextState_MoveOnWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walf.Custom", "bool IsInWater()", IsInWater, t_Custom_IsInWater);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Walf.Custom", "bool IsFloating()", IsFloating, t_Custom_IsFloating);
}

}

}
}
}
}
