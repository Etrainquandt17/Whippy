#include "scn/step/enemy/degout/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/degout/Custom.h"
#include "scn/step/enemy/degout/StateChase.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace degout {

namespace {

void t_SetNextState_Chase() {
    MintEnemy::Obj()->stateChanger().setNextState<StateChase, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsChaseFlag() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isChaseFlag();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Degout.SetNextState", "void Chase()", Chase, t_SetNextState_Chase);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Degout.Custom", "bool IsChaseFlag()", IsChaseFlag, t_Custom_IsChaseFlag);
}

}

}}}}  // namespace scn::step::enemy::degout
