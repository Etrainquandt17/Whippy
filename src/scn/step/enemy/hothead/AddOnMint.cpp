#include "scn/step/enemy/hothead/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/hothead/Custom.h"
#include "scn/step/enemy/hothead/StateAttackBreath.h"
#include "scn/step/enemy/hothead/StateAttackShot.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

namespace {

void t_SetNextState_AttackBreath() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttackBreath, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_AttackShot() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttackShot, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsPlayerPosNear() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isPlayerPosNear();
}

bool t_Custom_IsInViewRect() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isInViewRect();
}

int t_Custom_SetAfterAttackFrame() {
    return DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setAfterAttackFrame();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.HotHead.SetNextState", "void AttackBreath()", AttackBreath, t_SetNextState_AttackBreath);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.HotHead.SetNextState", "void AttackShot()", AttackShot, t_SetNextState_AttackShot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.HotHead.Custom", "bool IsPlayerPosNear()", IsPlayerPosNear, t_Custom_IsPlayerPosNear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.HotHead.Custom", "bool IsInViewRect()", IsInViewRect, t_Custom_IsInViewRect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.HotHead.Custom", "int SetAfterAttackFrame()", SetAfterAttackFrame, t_Custom_SetAfterAttackFrame);
}

}

}}}}  // namespace scn::step::enemy::hothead
