#include "scn/step/enemy/leaper/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateShootingComeInZ.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/leaper/Custom.h"
#include "scn/step/enemy/leaper/StateBackAndForthAttack.h"
#include "scn/step/enemy/leaper/StateFlyAttack.h"

using hel::common::DynamicCastToRef;

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

namespace {

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_FlyAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFlyAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_BackAndForthAttack() {
    MintEnemy::Obj()->stateChanger().setNextState<StateBackAndForthAttack, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_ComeInZFar() {
    common::StateShootingComeInZ::Config config;
    config._0 = true;
    config._1 = true;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingComeInZ, Enemy*, common::StateShootingComeInZ::Config>(MintEnemy::Obj(), config);
}

void t_SetNextState_ComeInZNear() {
    common::StateShootingComeInZ::Config config;
    config._0 = false;
    config._1 = true;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingComeInZ, Enemy*, common::StateShootingComeInZ::Config>(MintEnemy::Obj(), config);
}

void t_Custom_SetBodyColl() {
    DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setBodyColl();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.SetNextState", "void FlyAttack()", FlyAttack, t_SetNextState_FlyAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.SetNextState", "void BackAndForthAttack()", BackAndForthAttack, t_SetNextState_BackAndForthAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.SetNextState", "void ComeInZFar()", ComeInZFar, t_SetNextState_ComeInZFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.SetNextState", "void ComeInZNear()", ComeInZNear, t_SetNextState_ComeInZNear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Leaper.Custom", "void SetBodyColl()", SetBodyColl, t_Custom_SetBodyColl);
}

}

}}}}  // namespace scn::step::enemy::leaper
