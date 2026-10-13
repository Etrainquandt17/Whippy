#include "scn/step/enemy/gigatzo/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/gigatzo/Custom.h"
#include "scn/step/enemy/gigatzo/StateAim.h"
#include "scn/step/enemy/gigatzo/StateAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace gigatzo {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Aim() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAim, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsPlayerInAimArea() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInAimArea();
}

int t_Custom_SetWaitAttackTime() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setWaitAttackTime();
}

int t_Custom_SetWaitBackAttackTime() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setWaitBackAttackTime();
}

int t_Custom_SetWaitBackAttackMoreTime() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setWaitBackAttackMoreTime();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.SetNextState", "void Aim()", Aim, t_SetNextState_Aim);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.Custom", "bool IsPlayerInAimArea()", IsPlayerInAimArea, t_Custom_IsPlayerInAimArea);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.Custom", "int SetWaitAttackTime()", SetWaitAttackTime, t_Custom_SetWaitAttackTime);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.Custom", "int SetWaitBackAttackTime()", SetWaitBackAttackTime, t_Custom_SetWaitBackAttackTime);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Gigatzo.Custom", "int SetWaitBackAttackMoreTime()", SetWaitBackAttackMoreTime, t_Custom_SetWaitBackAttackMoreTime);
}

}

}}}}  // namespace scn::step::enemy::gigatzo
