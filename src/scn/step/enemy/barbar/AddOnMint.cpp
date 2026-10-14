#include "scn/step/enemy/barbar/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/barbar/Custom.h"
#include "scn/step/enemy/barbar/StateAttack.h"
#include "scn/step/enemy/barbar/StateWait.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsPlayerInArea() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerInArea();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Barbar.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Barbar.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Barbar.Custom", "bool IsPlayerInArea()", IsPlayerInArea, t_Custom_IsPlayerInArea);
}

}

}}}}  // namespace scn::step::enemy::barbar
