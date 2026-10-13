#include "scn/step/boss/dubior/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/dubior/StateCall.h"
#include "scn/step/boss/dubior/StateDash.h"
#include "scn/step/boss/dubior/StateGlide.h"
#include "scn/step/boss/dubior/StateHeightAdjust.h"
#include "scn/step/boss/dubior/StateMoveThunderStart.h"
#include "scn/step/boss/dubior/StateMoveToOtherSide.h"
#include "scn/step/boss/dubior/StateShot.h"
#include "scn/step/boss/dubior/StateThunderStart.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace dubior {

namespace {

void t_SetNextState_Call(int kind) {
    MintBoss::Obj().stateChanger().setNextState<StateCall, Boss*, u32>(&MintBoss::Obj(), kind);
}

void t_SetNextState_MoveToOtherSide() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveToOtherSide, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_HeightAdjust() {
    MintBoss::Obj().stateChanger().setNextState<StateHeightAdjust, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Dash() {
    MintBoss::Obj().stateChanger().setNextState<StateDash, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Glide() {
    MintBoss::Obj().stateChanger().setNextState<StateGlide, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Thunder() {
    MintBoss::Obj().stateChanger().setNextState<StateThunderStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MoveThunder() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveThunderStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Shot(f32 speed) {
    MintBoss::Obj().stateChanger().setNextState<StateShot, Boss*, f32>(&MintBoss::Obj(), speed);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void Call(int)", Call, t_SetNextState_Call);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void MoveToOtherSide()", MoveToOtherSide, t_SetNextState_MoveToOtherSide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void HeightAdjust()", HeightAdjust, t_SetNextState_HeightAdjust);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void Dash()", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void Glide()", Glide, t_SetNextState_Glide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void Thunder()", Thunder, t_SetNextState_Thunder);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void MoveThunder()", MoveThunder, t_SetNextState_MoveThunder);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Dubior.SetNextState", "void Shot(float)", Shot, t_SetNextState_Shot);
}

}

}
}
}
}
