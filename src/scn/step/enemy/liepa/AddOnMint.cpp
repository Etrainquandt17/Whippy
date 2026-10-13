#include "scn/step/enemy/liepa/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateShootingComeInZ.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/common/StateShootingMove.h"
#include "scn/step/enemy/liepa/Custom.h"
#include "scn/step/enemy/liepa/StateCircleAttack.h"
#include "scn/step/enemy/liepa/StateFlyAttack.h"
#include "scn/step/enemy/liepa/StateMoveAttack.h"

namespace scn {
namespace step {
namespace enemy {
namespace liepa {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom());
}

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_FlyAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFlyAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_CircleAttack(int count) {
    StateCircleAttack::Config config;
    config._0 = count;
    MintEnemy::Obj()->stateChanger().setNextState<StateCircleAttack, Enemy*, StateCircleAttack::Config>(MintEnemy::Obj(), config);
}

void t_SetNextState_Move(f32 x, f32 y) {
    common::StateShootingMove::Config config;
    config._0 = x;
    config._4 = y;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingMove, Enemy*, common::StateShootingMove::Config>(MintEnemy::Obj(), config);
}

void t_SetNextState_MoveAttack(f32 value) {
    StateMoveAttack::Config config;
    config._0 = value;
    MintEnemy::Obj()->stateChanger().setNextState<StateMoveAttack, Enemy*, StateMoveAttack::Config>(MintEnemy::Obj(), config);
}

void t_SetNextState_ComeInZFar() {
    common::StateShootingComeInZ::Config config;
    config._0 = true;
    config._1 = false;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingComeInZ, Enemy*, common::StateShootingComeInZ::Config>(MintEnemy::Obj(), config);
}

void t_SetNextState_ComeInZNear() {
    common::StateShootingComeInZ::Config config;
    config._0 = false;
    config._1 = false;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingComeInZ, Enemy*, common::StateShootingComeInZ::Config>(MintEnemy::Obj(), config);
}

bool t_Custom_IsExistHeroInAttackRange() {
    return t_custom().isExistHeroInAttackRange();
}

void t_Custom_SetBodyColl() {
    t_custom().setBodyColl();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void FlyAttack()", FlyAttack, t_SetNextState_FlyAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void CircleAttack(int)", CircleAttack, t_SetNextState_CircleAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void Move(float,float)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void MoveAttack(float)", MoveAttack, t_SetNextState_MoveAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void ComeInZFar()", ComeInZFar, t_SetNextState_ComeInZFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.SetNextState", "void ComeInZNear()", ComeInZNear, t_SetNextState_ComeInZNear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.Custom", "bool IsExistHeroInAttackRange()", IsExistHeroInAttackRange, t_Custom_IsExistHeroInAttackRange);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Liepa.Custom", "void SetBodyColl()", SetBodyColl, t_Custom_SetBodyColl);
}

}

}
}
}
}
