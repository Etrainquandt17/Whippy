#include "scn/step/enemy/dubiorjr/AddOnMint.h"

// Ahead of WrapNative.h: the instances of a template that is declared earlier come later in the unit.
#include "hel/common/RuntimeTypeInfo.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/Param.h"
#include "scn/step/enemy/dubiorjr/ParamData.h"
#include "scn/step/enemy/dubiorjr/StateBack.h"
#include "scn/step/enemy/dubiorjr/StateFly.h"
#include "scn/step/enemy/dubiorjr/StateMove.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

namespace {

void t_SetNextState_Fly(f32 value) {
    MintEnemy::Obj()->stateChanger().setNextState<StateFly, Enemy*, f32>(MintEnemy::Obj(), value);
}

void t_SetNextState_Move(f32 value) {
    const ParamData& param = MintEnemy::Obj()->param().dubiorjr();
    Enemy* enemy = MintEnemy::Obj();
    MintEnemy::Obj()->stateChanger().setNextState<StateMove, Enemy*, f32, f32>(enemy, value, param._4);
}

void t_SetNextState_Dash(f32 value) {
    const ParamData& param = MintEnemy::Obj()->param().dubiorjr();
    Enemy* enemy = MintEnemy::Obj();
    MintEnemy::Obj()->stateChanger().setNextState<StateMove, Enemy*, f32, f32>(enemy, value, param._10);
}

void t_SetNextState_Back(f32 value) {
    MintEnemy::Obj()->stateChanger().setNextState<StateBack, Enemy*, f32>(MintEnemy::Obj(), value);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DubiorJr.SetNextState", "void Fly(float)", Fly, t_SetNextState_Fly);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DubiorJr.SetNextState", "void Move(float)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DubiorJr.SetNextState", "void Dash(float)", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.DubiorJr.SetNextState", "void Back(float)", Back, t_SetNextState_Back);
}

}

}
}
}
}
