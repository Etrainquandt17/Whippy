#include "scn/step/enemy/sirkibble/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/sirkibble/Custom.h"
#include "scn/step/enemy/sirkibble/StateAttack.h"
#include "scn/step/enemy/sirkibble/StateJump.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

namespace {

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_Custom_ChkPlayerPos() {
    DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).chkPlayerPos();
}

bool t_Custom_IsPlayerUpPos() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerUpPos();
}

bool t_Custom_IsChangeDirType() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isChangeDirType();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SirKibble.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SirKibble.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SirKibble.Custom", "void ChkPlayerPos()", ChkPlayerPos, t_Custom_ChkPlayerPos);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SirKibble.Custom", "bool IsPlayerUpPos()", IsPlayerUpPos, t_Custom_IsPlayerUpPos);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.SirKibble.Custom", "bool IsChangeDirType()", IsChangeDirType, t_Custom_IsChangeDirType);
}

}

}}}}  // namespace scn::step::enemy::sirkibble
