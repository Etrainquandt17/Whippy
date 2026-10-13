#include "scn/step/enemy/juckle/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/juckle/Custom.h"
#include "scn/step/enemy/juckle/StateAttack.h"
#include "scn/step/enemy/juckle/StateFollow.h"

namespace scn {
namespace step {
namespace enemy {
namespace juckle {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Follow() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFollow, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsPlayerInArea() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInArea();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Juckle.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Juckle.SetNextState", "void Follow()", Follow, t_SetNextState_Follow);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Juckle.Custom", "bool IsPlayerInArea()", IsPlayerInArea, t_Custom_IsPlayerInArea);
}

}

}
}
}
}
