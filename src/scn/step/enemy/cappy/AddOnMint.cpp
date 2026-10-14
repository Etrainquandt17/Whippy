#include "scn/step/enemy/cappy/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/cappy/Custom.h"
#include "scn/step/enemy/cappy/StateAttack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

u32 t_Custom_ThrowCount() {
    return t_custom().throwCount();
}

void t_Custom_SetThrowCount(u32 count) {
    t_custom().setThrowCount(count);
}

bool t_Custom_Cap() {
    return t_custom().cap();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Cappy.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Cappy.Custom", "int ThrowCount()", ThrowCount, t_Custom_ThrowCount);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Cappy.Custom", "void SetThrowCount(int)", SetThrowCount, t_Custom_SetThrowCount);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Cappy.Custom", "bool Cap()", Cap, t_Custom_Cap);
}

}

}}}}  // namespace scn::step::enemy::cappy
