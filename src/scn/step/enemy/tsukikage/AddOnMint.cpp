#include "scn/step/enemy/tsukikage/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/tsukikage/Custom.h"
#include "scn/step/enemy/tsukikage/StateAttack.h"
#include "scn/step/enemy/tsukikage/StateJump.h"
#include "scn/step/enemy/tsukikage/StateJumpAttack.h"
#include "scn/step/enemy/tsukikage/StateWait.h"
#include "scn/step/enemy/tsukikage/StateWall.h"
#include "scn/step/enemy/tsukikage/StateWallAttack.h"
#include "scn/step/enemy/tsukikage/StateWarp.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

namespace {

void t_SetNextState_Jump() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJump, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Attack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_WallAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWallAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_JumpAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateJumpAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Warp() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWarp, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Wall() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWall, Enemy*>(MintEnemy::Obj());
}

bool t_Custom_IsWall() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isWall();
}

bool t_Custom_IsJumpAttack() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isJumpAttack();
}

bool t_Custom_IsFirstAppear() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isFirstAppear();
}

bool t_Custom_IsWallAttack() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).isWallAttack();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void WallAttack()", WallAttack, t_SetNextState_WallAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void JumpAttack()", JumpAttack, t_SetNextState_JumpAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void Warp()", Warp, t_SetNextState_Warp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.SetNextState", "void Wall()", Wall, t_SetNextState_Wall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.Custom", "bool IsWall()", IsWall, t_Custom_IsWall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.Custom", "bool IsJumpAttack()", IsJumpAttack, t_Custom_IsJumpAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.Custom", "bool IsFirstAppear()", IsFirstAppear, t_Custom_IsFirstAppear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Tsukikage.Custom", "bool IsWallAttack()", IsWallAttack, t_Custom_IsWallAttack);
}

}

}}}}  // namespace scn::step::enemy::tsukikage
