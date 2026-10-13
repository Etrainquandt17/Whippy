#include "scn/step/enemy/bowby/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/bowby/Custom.h"
#include "scn/step/enemy/bowby/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace bowby {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsPlayerInArea() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInArea();
}

bool t_Custom_IsAnimStart() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isAnimStart();
}

void t_Custom_OffAnimStart() {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setAnimStart(false);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bowby.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bowby.Custom", "bool IsPlayerInArea()", IsPlayerInArea, t_Custom_IsPlayerInArea);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bowby.Custom", "bool IsAnimStart()", IsAnimStart, t_Custom_IsAnimStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Bowby.Custom", "void OffAnimStart()", OffAnimStart, t_Custom_OffAnimStart);
}

}

}
}
}
}
