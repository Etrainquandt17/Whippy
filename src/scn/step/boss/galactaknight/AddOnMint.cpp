#include "scn/step/boss/galactaknight/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/galactaknight/AttackDesc.h"
#include "scn/step/boss/galactaknight/Custom.h"
#include "scn/step/boss/galactaknight/JumpDesc.h"
#include "scn/step/boss/galactaknight/ScriptKind.h"
#include "scn/step/boss/galactaknight/StateAttack.h"
#include "scn/step/boss/galactaknight/StateBlastShot.h"
#include "scn/step/boss/galactaknight/StateDash.h"
#include "scn/step/boss/galactaknight/StateDeadEscape.h"
#include "scn/step/boss/galactaknight/StateFlyUpFar.h"
#include "scn/step/boss/galactaknight/StateFlyZ.h"
#include "scn/step/boss/galactaknight/StateGiantTornado.h"
#include "scn/step/boss/galactaknight/StateGlideSword.h"
#include "scn/step/boss/galactaknight/StateGuard.h"
#include "scn/step/boss/galactaknight/StateJump.h"
#include "scn/step/boss/galactaknight/StateJumpEnd.h"
#include "scn/step/boss/galactaknight/StateMince.h"
#include "scn/step/boss/galactaknight/StateRevolutionSword.h"
#include "scn/step/boss/galactaknight/StateShuttleLoop.h"
#include "scn/step/boss/galactaknight/StateSpinAttackCharge.h"
#include "scn/step/boss/galactaknight/StateStep.h"
#include "scn/step/boss/galactaknight/StateSwordBeamAttack.h"
#include "scn/step/boss/galactaknight/StateThunderSpine.h"
#include "scn/step/boss/galactaknight/StateTornadoAttack.h"
#include "scn/step/boss/galactaknight/StateUnderThrust.h"
#include "scn/step/boss/galactaknight/SwordBeamCtrl.h"
#include "scn/step/boss/galactaknight/ThunderSpineCtrl.h"

using hel::common::DynamicCastToRef;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_BackStep(f32 a, f32 b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateStep, Boss*, ScriptKind, f32, f32, u32>(&MintBoss::Obj(), ScriptKind_BackStep, a, b, c);
}

void t_SetNextState_AirJumpFall(f32 a, f32 b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateStep, Boss*, ScriptKind, f32, f32, u32>(&MintBoss::Obj(), ScriptKind_AirJumpFall, a, b, c);
}

void t_SetNextState_Jump(f32 a, f32 b, int c, bool d, bool e) {
    JumpDesc desc(ScriptKind_Jump, a, b, c);
    desc._10 = d;
    desc._13 = e;
    MintBoss::Obj().stateChanger().setNextState<StateJump, Boss*, JumpDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_JumpFront(f32 a, int b) {
    JumpDesc desc(ScriptKind_Jump, 0.0f, a, b);
    desc._10 = true;
    desc._11 = true;
    desc._14 = true;
    MintBoss::Obj().stateChanger().setNextState<StateJump, Boss*, JumpDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_JumpFar(f32 a, f32 b, int c) {
    JumpDesc desc(ScriptKind_Jump, a, b, c);
    desc._10 = true;
    desc._11 = true;
    desc._12 = true;
    MintBoss::Obj().stateChanger().setNextState<StateJump, Boss*, JumpDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_JumpEnd(f32 a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpEnd, Boss*, ScriptKind, f32, u32>(&MintBoss::Obj(), ScriptKind_JumpEnd, a, b);
}

void t_SetNextState_Walk(f32 a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateStep, Boss*, ScriptKind, f32, f32, u32>(&MintBoss::Obj(), ScriptKind_Walk, a, 0.0f, b);
}

void t_SetNextState_Dash(f32 a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateDash, Boss*, f32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_FlyZ(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateFlyZ, Boss*, f32>(&MintBoss::Obj(), a);
}

void t_SetNextState_FlyUpFar(f32 a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateFlyUpFar, Boss*, f32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_Guard(f32 a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateGuard, Boss*, f32, u32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_Attack1(f32 a, int b, bool c) {
    AttackDesc desc(ScriptKind_Attack1, a, b, false);
    desc._D = c;
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_Attack2(f32 a, int b, bool c) {
    AttackDesc desc(ScriptKind_Attack2, a, b, false);
    desc._D = c;
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_Attack3(f32 a, int b, bool c) {
    AttackDesc desc(ScriptKind_Attack3, a, b, true);
    desc._D = c;
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_AttackMince() {
    MintBoss::Obj().stateChanger().setNextState<StateMince, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_AttackFinish(f32 a, int b) {
    AttackDesc desc(ScriptKind_AttackFinish, a, b, true);
    desc._D = true;
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_AttackHi() {
    AttackDesc desc(ScriptKind_AttackHi, true);
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_AirSpin(f32 a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpEnd, Boss*, ScriptKind, f32, u32>(&MintBoss::Obj(), ScriptKind_AirSpin, a, b);
}

void t_SetNextState_AirSpinFall(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpEnd, Boss*, ScriptKind, f32, u32>(&MintBoss::Obj(), ScriptKind_AirSpinFall, 0.0f, a);
}

void t_SetNextState_BlastShot() {
    MintBoss::Obj().stateChanger().setNextState<StateBlastShot, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_AttackThrust(f32 a, int b) {
    AttackDesc desc(ScriptKind_AttackThrust, a, b, false);
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_AttackThrustEnd() {
    AttackDesc desc(ScriptKind_AttackThrustEnd, true);
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, AttackDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_SpinAttack(int a, f32 b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateSpinAttackCharge, Boss*, u32, f32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_UnderThrust() {
    MintBoss::Obj().stateChanger().setNextState<StateUnderThrust, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_GiantTornado(int a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateGiantTornado, Boss*, u32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_ThunderSpine() {
    MintBoss::Obj().stateChanger().setNextState<StateThunderSpine, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_RevolutionSword() {
    MintBoss::Obj().stateChanger().setNextState<StateRevolutionSword, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SwordBeamAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateSwordBeamAttack, Boss*, ScriptKind>(&MintBoss::Obj(), ScriptKind_SwordBeamAttack);
}

void t_SetNextState_SwordBeamRain() {
    MintBoss::Obj().stateChanger().setNextState<StateSwordBeamAttack, Boss*, ScriptKind>(&MintBoss::Obj(), ScriptKind_SwordBeamRain);
}

void t_SetNextState_TornadoAttackRise(f32 a, u32 b) {
    JumpDesc desc(ScriptKind_TornadoAttackRise, 0.0f, a, b);
    MintBoss::Obj().stateChanger().setNextState<StateJump, Boss*, JumpDesc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_TornadoAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_GlideSword(bool a) {
    MintBoss::Obj().stateChanger().setNextState<StateShuttleLoop, Boss*, bool>(&MintBoss::Obj(), a);
}

void t_SetNextState_GlideSwordOutSide(f32 a, bool b) {
    MintBoss::Obj().stateChanger().setNextState<StateGlideSword, Boss*, f32, bool>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_DeadEscape() {
    MintBoss::Obj().stateChanger().setNextState<StateDeadEscape, Boss*>(&MintBoss::Obj());
}

void t_ThunderSpineCtrl_Add(f32 a) {
    ThunderSpineCtrl::ReqData data;
    data._0 = a;
    t_custom().thunderSpineCtrl().add(data);
}

void t_ThunderSpineCtrl_Clear() {
    t_custom().thunderSpineCtrl().clear();
}

f32 t_LandCtrl_GetCenterX() {
    return t_custom().landCtrl().getCenterX();
}

f32 t_LandCtrl_GetHalfWidth() {
    return 0.5f * t_custom().landCtrl().getWidth();
}

bool t_LandCtrl_IsGround() {
    return t_custom().landCtrl().isGround();
}

void t_SwordBeamCtrl_Add(f32 a) {
    SwordBeamCtrl::ReqData data;
    data._0 = a;
    data._4 = false;
    t_custom().swordBeamCtrl().add(data);
}

void t_SwordBeamCtrl_AddFar(f32 a, bool b) {
    SwordBeamCtrl::ReqData data;
    data._0 = a;
    data._4 = true;
    data._5 = b;
    t_custom().swordBeamCtrl().add(data);
}

void t_SwordBeamCtrl_Clear() {
    t_custom().swordBeamCtrl().clear();
}

void t_SwordBeamCtrl_ShuffleIndex() {
    t_custom().swordBeamCtrl().shuffleIndex();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void BackStep(float,float,int)", BackStep, t_SetNextState_BackStep);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AirJumpFall(float,float,int)", AirJumpFall,
                         t_SetNextState_AirJumpFall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Jump(float,float,int,bool,bool)", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void JumpFront(float,int)", JumpFront, t_SetNextState_JumpFront);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void JumpFar(float,float,int)", JumpFar, t_SetNextState_JumpFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void JumpEnd(float,int)", JumpEnd, t_SetNextState_JumpEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Walk(float,int)", Walk, t_SetNextState_Walk);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Dash(float,float)", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void FlyZ(float)", FlyZ, t_SetNextState_FlyZ);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void FlyUpFar(float,float)", FlyUpFar, t_SetNextState_FlyUpFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Guard(float,int,int)", Guard, t_SetNextState_Guard);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Attack1(float,int,bool)", Attack1, t_SetNextState_Attack1);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Attack2(float,int,bool)", Attack2, t_SetNextState_Attack2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void Attack3(float,int,bool)", Attack3, t_SetNextState_Attack3);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AttackMince()", AttackMince, t_SetNextState_AttackMince);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AttackFinish(float,int)", AttackFinish,
                         t_SetNextState_AttackFinish);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AttackHi()", AttackHi, t_SetNextState_AttackHi);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AirSpin(float,int)", AirSpin, t_SetNextState_AirSpin);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AirSpinFall(int)", AirSpinFall, t_SetNextState_AirSpinFall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void BlastShot()", BlastShot, t_SetNextState_BlastShot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AttackThrust(float,int)", AttackThrust,
                         t_SetNextState_AttackThrust);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void AttackThrustEnd()", AttackThrustEnd,
                         t_SetNextState_AttackThrustEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void SpinAttack(int,float,int)", SpinAttack,
                         t_SetNextState_SpinAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void UnderThrust()", UnderThrust, t_SetNextState_UnderThrust);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void GiantTornado(int,float)", GiantTornado,
                         t_SetNextState_GiantTornado);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void ThunderSpine()", ThunderSpine, t_SetNextState_ThunderSpine);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void RevolutionSword()", RevolutionSword,
                         t_SetNextState_RevolutionSword);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void SwordBeamAttack()", SwordBeamAttack,
                         t_SetNextState_SwordBeamAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void SwordBeamRain()", SwordBeamRain,
                         t_SetNextState_SwordBeamRain);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void TornadoAttackRise(float,int)", TornadoAttackRise,
                         reinterpret_cast<void (*)(f32, int)>(t_SetNextState_TornadoAttackRise));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void TornadoAttack()", TornadoAttack,
                         t_SetNextState_TornadoAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void GlideSword(bool)", GlideSword, t_SetNextState_GlideSword);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void GlideSwordOutSide(float,bool)", GlideSwordOutSide,
                         t_SetNextState_GlideSwordOutSide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SetNextState", "void DeadEscape()", DeadEscape, t_SetNextState_DeadEscape);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.ThunderSpineCtrl", "void Add(float)", Add, t_ThunderSpineCtrl_Add);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.ThunderSpineCtrl", "void Clear()", Clear, t_ThunderSpineCtrl_Clear);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.LandCtrl", "float GetCenterX()", GetCenterX, t_LandCtrl_GetCenterX);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.LandCtrl", "float GetHalfWidth()", GetHalfWidth, t_LandCtrl_GetHalfWidth);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.LandCtrl", "bool IsGround()", IsGround, t_LandCtrl_IsGround);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SwordBeamCtrl", "void Add(float)", Add, t_SwordBeamCtrl_Add);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SwordBeamCtrl", "void AddFar(float,bool)", AddFar, t_SwordBeamCtrl_AddFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SwordBeamCtrl", "void Clear()", Clear, t_SwordBeamCtrl_Clear);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GalactaKnight.SwordBeamCtrl", "void ShuffleIndex()", ShuffleIndex, t_SwordBeamCtrl_ShuffleIndex);
}

}

}}}}  // namespace scn::step::boss::galactaknight
