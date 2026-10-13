#include "scn/step/boss/mahoroabattle1/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/mahoroabattle1/BarrierCtrl.h"
#include "scn/step/boss/mahoroabattle1/Custom.h"
#include "scn/step/boss/mahoroabattle1/EnemyCtrl.h"
#include "scn/step/boss/mahoroabattle1/LowperType.h"
#include "scn/step/boss/mahoroabattle1/MagicBallCtrl.h"
#include "scn/step/boss/mahoroabattle1/NeedleCtrl.h"
#include "scn/step/boss/mahoroabattle1/ScriptKind.h"
#include "scn/step/boss/mahoroabattle1/StateAbilityOffAttack.h"
#include "scn/step/boss/mahoroabattle1/StateBeam.h"
#include "scn/step/boss/mahoroabattle1/StateBlackHole.h"
#include "scn/step/boss/mahoroabattle1/StateEnemyCall.h"
#include "scn/step/boss/mahoroabattle1/StateEnergyCharge.h"
#include "scn/step/boss/mahoroabattle1/StateMagicBallAttack.h"
#include "scn/step/boss/mahoroabattle1/StateMagicBallAttackWarpIn.h"
#include "scn/step/boss/mahoroabattle1/StateMagicBallAttackWarpOut.h"
#include "scn/step/boss/mahoroabattle1/StateMagicBallCharge.h"
#include "scn/step/boss/mahoroabattle1/StateMove.h"
#include "scn/step/boss/mahoroabattle1/StateMoveFar.h"
#include "scn/step/boss/mahoroabattle1/StateNeedleAttack.h"
#include "scn/step/boss/mahoroabattle1/StateNeedleAttackCharge.h"
#include "scn/step/boss/mahoroabattle1/StateNeedleAttackEnd.h"
#include "scn/step/boss/mahoroabattle1/StateRevolutionAttack.h"
#include "scn/step/boss/mahoroabattle1/StateRevolutionAttackEnd.h"
#include "scn/step/boss/mahoroabattle1/StateRevolutionAttackStart.h"
#include "scn/step/boss/mahoroabattle1/StateStormStart.h"
#include "scn/step/boss/mahoroabattle1/StateSummonLowper.h"
#include "scn/step/boss/mahoroabattle1/StateTackleStart.h"
#include "scn/step/boss/mahoroabattle1/StateWarpHoleAttackMagicBall.h"
#include "scn/step/boss/mahoroabattle1/StateWarpHoleAttackNeedle.h"
#include "scn/step/boss/mahoroabattle1/StateWarpHoleAttackStart.h"
#include "scn/step/boss/mahoroabattle1/StateWarpIn.h"
#include "scn/step/boss/mahoroabattle1/StateWarpOut.h"
#include "scn/step/boss/mahoroabattle1/StormCtrl.h"
#include "scn/step/boss/mahoroabattle1/WarpHoleCtrl.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle1 {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_WarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpIn, Boss*, bool>(&MintBoss::Obj(), false);
}

// TODO: the original passes the temporary to setNextState by value without copying it; the reference stands in
// for that (see util/StateChanger.h), here and in every state change below that names the vector as one.
void t_SetNextState_WarpOut(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpOut, Boss*, const hel::math::Vector3&>(&MintBoss::Obj(), hel::math::Vector3(x, y, z));
}

void t_SetNextState_NeedleAttackCharge() {
    MintBoss::Obj().stateChanger().setNextState<StateNeedleAttackCharge, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_NeedleAttack(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateNeedleAttack, Boss*, u32, ScriptKind>(&MintBoss::Obj(), index, ScriptKind_NeedleAttack);
}

void t_SetNextState_NeedleAttackL(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateNeedleAttack, Boss*, u32, ScriptKind>(&MintBoss::Obj(), index, ScriptKind_NeedleAttackL);
}

void t_SetNextState_NeedleAttackR(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateNeedleAttack, Boss*, u32, ScriptKind>(&MintBoss::Obj(), index, ScriptKind_NeedleAttackR);
}

void t_SetNextState_NeedleAttackEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateNeedleAttackEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Tackle(f32 x, f32 y, f32 z, int a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateTackleStart, Boss*, const hel::math::Vector3&, u32, f32>(
        &MintBoss::Obj(), hel::math::Vector3(x, y, z), a, b);
}

void t_SetNextState_MagicBallCharge() {
    MintBoss::Obj().stateChanger().setNextState<StateMagicBallCharge, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MagicBallAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateMagicBallAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MagicBallAttackWarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateMagicBallAttackWarpIn, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MagicBallAttackWarpOut(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateMagicBallAttackWarpOut, Boss*, const hel::math::Vector3&>(
        &MintBoss::Obj(), hel::math::Vector3(x, y, z));
}

void t_SetNextState_RevolutionAttackStart() {
    MintBoss::Obj().stateChanger().setNextState<StateRevolutionAttackStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_RevolutionAttack(f32 x, f32 y) {
    MintBoss::Obj().stateChanger().setNextState<StateRevolutionAttack, Boss*, hel::math::Vector2>(&MintBoss::Obj(), hel::math::Vector2(x, y));
}

void t_SetNextState_RevolutionAttackEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateRevolutionAttackEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BlackHole() {
    MintBoss::Obj().stateChanger().setNextState<StateBlackHole, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Beam() {
    MintBoss::Obj().stateChanger().setNextState<StateBeam, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_EnemyCall(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateEnemyCall, Boss*, u32>(&MintBoss::Obj(), index);
}

void t_SetNextState_SummonLowper(int type, int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateSummonLowper, Boss*, LowperType, u32, u32>(
        &MintBoss::Obj(), static_cast<LowperType>(type), a, b);
}

void t_SetNextState_Move(f32 x, f32 y, f32 z, u32 time) {
    MintBoss::Obj().stateChanger().setNextState<StateMove, Boss*, const hel::math::Vector3&, u32>(&MintBoss::Obj(), hel::math::Vector3(x, y, z), time);
}

void t_SetNextState_MoveFar(f32 x, f32 y, f32 z, u32 time) {
    MintBoss::Obj().stateChanger().setNextState<StateMoveFar, Boss*, const hel::math::Vector3&, u32>(&MintBoss::Obj(), hel::math::Vector3(x, y, z), time);
}

void t_SetNextState_AbilityOffAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateAbilityOffAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_EnergyCharge() {
    MintBoss::Obj().stateChanger().setNextState<StateEnergyCharge, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_StormStart() {
    MintBoss::Obj().stateChanger().setNextState<StateStormStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpHoleAttack(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttackStart, Boss*, const hel::math::Vector3&>(
        &MintBoss::Obj(), hel::math::Vector3(x, y, z));
}

void t_SetNextState_WarpHoleAttackNeedle() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttackNeedle, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpHoleAttackMagicBall() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttackMagicBall, Boss*>(&MintBoss::Obj());
}

void t_Custom_AddReqNeedleBuff(int a, f32 b) {
    t_custom().needleCtrl().addReqBuff(a, b);
}

void t_Custom_ClearReqNeedleBuff() {
    t_custom().needleCtrl().clearBuff();
}

void t_Custom_ReqNeedleReady(int index) {
    t_custom().needleCtrl().request(index);
}

void t_Custom_ReqNeedleStart(int index) {
    t_custom().needleCtrl().reqStateStart(index);
}

void t_Custom_AddReqEnemyBuff(int a, bool b) {
    EnemyCtrl::ReqData data;
    data._0 = a;
    data._4 = b;
    t_custom().enemyCtrl().addReqData(data);
}

void t_Custom_ClearReqEnemyBuff() {
    t_custom().enemyCtrl().clearReqData();
}

void t_Custom_AddReqMagicBallBuff(int a, int b, int c) {
    MagicBallCtrl::ReqData data = {b, c};
    t_custom().magicBallCtrl().addReqData(a, data);
}

void t_Custom_ClearReqMagicBallBuff() {
    t_custom().magicBallCtrl().clearReqData();
}

int t_Custom_GetBarrierHp() {
    return t_custom().barrierCtrl().barrierHp();
}

bool t_Custom_IsBarrierHealed() {
    return t_custom().barrierCtrl().isHealed();
}

void t_Custom_StormEnd() {
    t_custom().stormCtrl().end();
}

void t_Custom_ReqWarpHoleWithMagicBall(f32 x, f32 y) {
    t_custom().warpHoleCtrl().requestWithMagicBall(hel::math::Vector2(x, y));
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void WarpIn()", WarpIn, t_SetNextState_WarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void WarpOut(float,float,float)", WarpOut, t_SetNextState_WarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void NeedleAttackCharge()", NeedleAttackCharge,
                         t_SetNextState_NeedleAttackCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void NeedleAttack(int)", NeedleAttack,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_NeedleAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void NeedleAttackL(int)", NeedleAttackL,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_NeedleAttackL));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void NeedleAttackR(int)", NeedleAttackR,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_NeedleAttackR));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void NeedleAttackEnd()", NeedleAttackEnd,
                         t_SetNextState_NeedleAttackEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void Tackle(float,float,float,int,float)", Tackle,
                         t_SetNextState_Tackle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void MagicBallCharge()", MagicBallCharge,
                         t_SetNextState_MagicBallCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void MagicBallAttack()", MagicBallAttack,
                         t_SetNextState_MagicBallAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void MagicBallAttackWarpIn()", MagicBallAttackWarpIn,
                         t_SetNextState_MagicBallAttackWarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void MagicBallAttackWarpOut(float,float,float)",
                         MagicBallAttackWarpOut, t_SetNextState_MagicBallAttackWarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void RevolutionAttackStart()", RevolutionAttackStart,
                         t_SetNextState_RevolutionAttackStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void RevolutionAttack(float,float)", RevolutionAttack,
                         t_SetNextState_RevolutionAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void RevolutionAttackEnd()", RevolutionAttackEnd,
                         t_SetNextState_RevolutionAttackEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void BlackHole()", BlackHole, t_SetNextState_BlackHole);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void Beam()", Beam, t_SetNextState_Beam);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void EnemyCall(int)", EnemyCall,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_EnemyCall));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void SummonLowper(int,int,int)", SummonLowper,
                         t_SetNextState_SummonLowper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void Move(float,float,float,int)", Move,
                         reinterpret_cast<void (*)(f32, f32, f32, int)>(t_SetNextState_Move));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void MoveFar(float,float,float,int)", MoveFar,
                         reinterpret_cast<void (*)(f32, f32, f32, int)>(t_SetNextState_MoveFar));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void AbilityOffAttack()", AbilityOffAttack,
                         t_SetNextState_AbilityOffAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void EnergyCharge()", EnergyCharge, t_SetNextState_EnergyCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void StormStart()", StormStart, t_SetNextState_StormStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void WarpHoleAttack(float,float,float)", WarpHoleAttack,
                         t_SetNextState_WarpHoleAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void WarpHoleAttackNeedle()", WarpHoleAttackNeedle,
                         t_SetNextState_WarpHoleAttackNeedle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.SetNextState", "void WarpHoleAttackMagicBall()", WarpHoleAttackMagicBall,
                         t_SetNextState_WarpHoleAttackMagicBall);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void AddReqNeedleBuff(int,float)", AddReqNeedleBuff,
                         t_Custom_AddReqNeedleBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ClearReqNeedleBuff()", ClearReqNeedleBuff,
                         t_Custom_ClearReqNeedleBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ReqNeedleReady(int)", ReqNeedleReady,
                         reinterpret_cast<void (*)(u32)>(t_Custom_ReqNeedleReady));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ReqNeedleStart(int)", ReqNeedleStart,
                         reinterpret_cast<void (*)(u32)>(t_Custom_ReqNeedleStart));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void AddReqEnemyBuff(int,bool)", AddReqEnemyBuff, t_Custom_AddReqEnemyBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ClearReqEnemyBuff()", ClearReqEnemyBuff, t_Custom_ClearReqEnemyBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void AddReqMagicBallBuff(int,int,int)", AddReqMagicBallBuff,
                         t_Custom_AddReqMagicBallBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ClearReqMagicBallBuff()", ClearReqMagicBallBuff,
                         t_Custom_ClearReqMagicBallBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "int GetBarrierHp()", GetBarrierHp, t_Custom_GetBarrierHp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "bool IsBarrierHealed()", IsBarrierHealed, t_Custom_IsBarrierHealed);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void StormEnd()", StormEnd, t_Custom_StormEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle1.Custom", "void ReqWarpHoleWithMagicBall(float,float)", ReqWarpHoleWithMagicBall,
                         t_Custom_ReqWarpHoleWithMagicBall);
}

}

}}}}  // namespace scn::step::boss::mahoroabattle1
