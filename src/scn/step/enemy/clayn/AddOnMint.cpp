#include "scn/step/enemy/clayn/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/ICustomInfo.h"
#include "scn/step/enemy/MintEnemy.h"
#include "scn/step/enemy/clayn/Custom.h"
#include "scn/step/enemy/clayn/StateAppear.h"
#include "scn/step/enemy/clayn/StateDisappear.h"
#include "scn/step/enemy/clayn/StateFall.h"
#include "scn/step/enemy/clayn/StateHideWait.h"
#include "scn/step/enemy/clayn/StateWait.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

namespace {

void t_SetNextState_Fall() {
    MintEnemy::Obj()->stateChanger().setNextState<StateFall, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_HideWait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateHideWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Appear() {
    MintEnemy::Obj()->stateChanger().setNextState<StateAppear, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Wait() {
    MintEnemy::Obj()->stateChanger().setNextState<StateWait, Enemy*>(MintEnemy::Obj());
}

void t_SetNextState_Disappear() {
    MintEnemy::Obj()->stateChanger().setNextState<StateDisappear, Enemy*>(MintEnemy::Obj());
}

void t_Custom_SetRotate(f32 rotate) {
    hel::common::DynamicCastToRef<Custom, ICustom>(MintEnemy::Obj()->custom()).setRotate(rotate);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.SetNextState", "void Fall()", Fall, t_SetNextState_Fall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.SetNextState", "void HideWait()", HideWait, t_SetNextState_HideWait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.SetNextState", "void Appear()", Appear, t_SetNextState_Appear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.SetNextState", "void Disappear()", Disappear, t_SetNextState_Disappear);
    // TODO: SetRotate's wrapper has two registers swapped until MintFuncProxy::internal_getArg_addr adds mOffset to the index in a local first.
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Enemy.Clayn.Custom", "void SetRotate(float)", SetRotate, t_Custom_SetRotate);
}

}

}
}
}
}
