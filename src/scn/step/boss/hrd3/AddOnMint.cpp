#include "scn/step/boss/hrd3/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/hrd3/Custom.h"
#include "scn/step/boss/hrd3/LandCtrl.h"
#include "scn/step/boss/hrd3/PartsCtrl.h"
#include "scn/step/boss/hrd3/PilotCtrl.h"
#include "scn/step/boss/hrd3/StateBeam.h"
#include "scn/step/boss/hrd3/StateBeamFar.h"
#include "scn/step/boss/hrd3/StateFallFar.h"
#include "scn/step/boss/hrd3/StateFlyingBodyPressRise.h"
#include "scn/step/boss/hrd3/StateLariat.h"
#include "scn/step/boss/hrd3/StateLariatFar.h"
#include "scn/step/boss/hrd3/StateMissileFar.h"
#include "scn/step/boss/hrd3/StateMoveFar.h"
#include "scn/step/boss/hrd3/StatePressFall.h"
#include "scn/step/boss/hrd3/StatePressSearch.h"
#include "scn/step/boss/hrd3/StatePunch.h"
#include "scn/step/boss/hrd3/StatePunchFar.h"
#include "scn/step/boss/hrd3/StateRise.h"
#include "scn/step/boss/hrd3/StateSwingArmFar.h"
#include "scn/step/boss/hrd3/StateWaitFar.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Punch() {
    MintBoss::Obj().stateChanger().setNextState<StatePunch, Boss*, bool>(&MintBoss::Obj(), false);
}

void t_SetNextState_TriplePunch() {
    MintBoss::Obj().stateChanger().setNextState<StatePunch, Boss*, bool>(&MintBoss::Obj(), true);
}

void t_SetNextState_Beam() {
    MintBoss::Obj().stateChanger().setNextState<StateBeam, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Rise() {
    MintBoss::Obj().stateChanger().setNextState<StateRise, Boss*, bool>(&MintBoss::Obj(), false);
}

void t_SetNextState_RiseToFar() {
    MintBoss::Obj().stateChanger().setNextState<StateRise, Boss*, bool>(&MintBoss::Obj(), true);
}

void t_SetNextState_Press(int count) {
    MintBoss::Obj().stateChanger().setNextState<StatePressFall, Boss*, u32>(&MintBoss::Obj(), count);
}

void t_SetNextState_SearchPress(int time, int count) {
    MintBoss::Obj().stateChanger().setNextState<StatePressSearch, Boss*, u32, u32>(&MintBoss::Obj(), time, count);
}

void t_SetNextState_Lariat(int time, f32 speed) {
    MintBoss::Obj().stateChanger().setNextState<StateLariat, Boss*, u32, f32>(&MintBoss::Obj(), time, speed);
}

void t_SetNextState_FlyingBodyPress() {
    MintBoss::Obj().stateChanger().setNextState<StateFlyingBodyPressRise, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WaitFar() {
    MintBoss::Obj().stateChanger().setNextState<StateWaitFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MoveCenterFar(int time, f32 y, f32 z) {
    hel::math::Vector3 pos(t_custom().landCtrl().getCenterX(), y + t_custom().landCtrl().getFloorY(), z);
    MintBoss::Obj().stateChanger().setNextState<StateMoveFar, Boss*, u32, hel::math::Vector3>(&MintBoss::Obj(), time, pos);
}

void t_SetNextState_FallFar(int time, f32 y, f32 z) {
    hel::math::Vector3 pos(t_custom().landCtrl().getCenterX(), y + t_custom().landCtrl().getFloorY(), z);
    MintBoss::Obj().stateChanger().setNextState<StateFallFar, Boss*, u32, hel::math::Vector3>(&MintBoss::Obj(), time, pos);
}

void t_SetNextState_PunchFar() {
    MintBoss::Obj().stateChanger().setNextState<StatePunchFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_LariatFar(int count) {
    MintBoss::Obj().stateChanger().setNextState<StateLariatFar, Boss*, u32>(&MintBoss::Obj(), count);
}

void t_SetNextState_BeamFar() {
    MintBoss::Obj().stateChanger().setNextState<StateBeamFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MissileFar(int count) {
    MintBoss::Obj().stateChanger().setNextState<StateMissileFar, Boss*, u32>(&MintBoss::Obj(), count);
}

void t_SetNextState_SwingArmFar(int count) {
    MintBoss::Obj().stateChanger().setNextState<StateSwingArmFar, Boss*, u32>(&MintBoss::Obj(), count);
}

f32 t_LandCtrl_GetCenterX() {
    return t_custom().landCtrl().getCenterX();
}

f32 t_LandCtrl_GetFloorY() {
    return t_custom().landCtrl().getFloorY();
}

void t_PilotCtrl_Missile() {
    t_custom().pilotCtrl().launchMissile();
}

bool t_PartsCtrl_IsBrokenBodyAndNeedle() {
    return !t_custom().partsCtrl().isExistHipNeedle() && !t_custom().partsCtrl().isExistOutsideBody();
}

bool t_PartsCtrl_IsBrokenBody() {
    return !t_custom().partsCtrl().isExistOutsideBody();
}

void t_PartsCtrl_StartDrillSubAnim() {
    t_custom().partsCtrl().startDrillSubAnim();
}

void t_PartsCtrl_StartDrillSubAnimFast() {
    t_custom().partsCtrl().startDrillSubAnimFast();
}

void t_PartsCtrl_StopDrillSubAnim() {
    t_custom().partsCtrl().stopDrillSubAnim();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void Punch()", Punch, t_SetNextState_Punch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void TriplePunch()", TriplePunch, t_SetNextState_TriplePunch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void Beam()", Beam, t_SetNextState_Beam);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void Rise()", Rise, t_SetNextState_Rise);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void RiseToFar()", RiseToFar, t_SetNextState_RiseToFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void SearchPress(int,int)", SearchPress, t_SetNextState_SearchPress);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void Press(int)", Press, t_SetNextState_Press);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void Lariat(int,float)", Lariat, t_SetNextState_Lariat);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void FlyingBodyPress()", FlyingBodyPress, t_SetNextState_FlyingBodyPress);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void WaitFar()", WaitFar, t_SetNextState_WaitFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void MoveCenterFar(int,float,float)", MoveCenterFar, t_SetNextState_MoveCenterFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void FallFar(int,float,float)", FallFar, t_SetNextState_FallFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void PunchFar()", PunchFar, t_SetNextState_PunchFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void LariatFar(int)", LariatFar, t_SetNextState_LariatFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void BeamFar()", BeamFar, t_SetNextState_BeamFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void MissileFar(int)", MissileFar, t_SetNextState_MissileFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.SetNextState", "void SwingArmFar(int)", SwingArmFar, t_SetNextState_SwingArmFar);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.LandCtrl", "float GetCenterX()", GetCenterX, t_LandCtrl_GetCenterX);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.LandCtrl", "float GetFloorY()", GetFloorY, t_LandCtrl_GetFloorY);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PilotCtrl", "void Missile()", Missile, t_PilotCtrl_Missile);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PartsCtrl", "bool IsBrokenBodyAndNeedle()", IsBrokenBodyAndNeedle, t_PartsCtrl_IsBrokenBodyAndNeedle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PartsCtrl", "bool IsBrokenBody()", IsBrokenBody, t_PartsCtrl_IsBrokenBody);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PartsCtrl", "void StartDrillSubAnim()", StartDrillSubAnim, t_PartsCtrl_StartDrillSubAnim);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PartsCtrl", "void StartDrillSubAnimFast()", StartDrillSubAnimFast, t_PartsCtrl_StartDrillSubAnimFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.HRD3.PartsCtrl", "void StopDrillSubAnim()", StopDrillSubAnim, t_PartsCtrl_StopDrillSubAnim);
}

}

}}}}  // namespace scn::step::boss::hrd3
