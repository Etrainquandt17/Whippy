#include "scn/step/enemy/owgulf/AddOnMint.h"

#include "app/Random.h"
// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/common/StateFly.h"
#include "scn/step/enemy/owgulf/ParamData.h"
#include "scn/step/enemy/owgulf/StateAttack1Way.h"
#include "scn/step/enemy/owgulf/StateAttack3Way.h"
#include "scn/step/enemy/owgulf/StateFlyStraight.h"
#include "scn/step/enemy/owgulf/StateFlyWaitFix.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

namespace {

void t_SetNextState_Attack() {
    if (app::Random::RandU32(100) < MintEnemy::Obj()->param().owgulf()._1c) {
        MintEnemy::Obj()->stateChanger().setNextState<StateAttack1Way, Enemy*>(MintEnemy::Obj());
    } else {
        MintEnemy::Obj()->stateChanger().setNextState<StateAttack3Way, Enemy*>(MintEnemy::Obj());
    }
}

template <typename S>
void SetNextState() {
    MintEnemy::Obj()->stateChanger().setNextState<S, Enemy*>(MintEnemy::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Owgulf.SetNextState", "void Wait()", Wait, SetNextState<common::StateFly>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Owgulf.SetNextState", "void WaitFix()", WaitFix, SetNextState<StateFlyWaitFix>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Owgulf.SetNextState", "void FlyStraight()", FlyStraight, SetNextState<StateFlyStraight>);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Owgulf.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
}

}

}
}
}
}
