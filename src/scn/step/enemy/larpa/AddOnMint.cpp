#include "scn/step/enemy/larpa/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/common/StateShootingComeInZ.h"
#include "scn/step/enemy/common/StateShootingFly.h"
#include "scn/step/enemy/common/StateShootingMove.h"
#include "scn/step/enemy/larpa/Custom.h"

namespace scn {
namespace step {
namespace enemy {
namespace larpa {

namespace {

void t_SetNextState_Fly() {
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingFly, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Move(f32 x, f32 y) {
    common::StateShootingMove::Config config;
    config._0 = x;
    config._4 = y;
    MintEnemy::Obj()->stateChanger().setNextState<common::StateShootingMove, Enemy*, common::StateShootingMove::Config>(MintEnemy::Obj(), config);
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

void t_Custom_SetBodyColl() {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setBodyColl();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Larpa.SetNextState", "void Fly()", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Larpa.SetNextState", "void Move(float,float)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Larpa.SetNextState", "void ComeInZFar()", ComeInZFar, t_SetNextState_ComeInZFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Larpa.SetNextState", "void ComeInZNear()", ComeInZNear, t_SetNextState_ComeInZNear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Larpa.Custom", "void SetBodyColl()", SetBodyColl, t_Custom_SetBodyColl);
}

}

}
}
}
}
