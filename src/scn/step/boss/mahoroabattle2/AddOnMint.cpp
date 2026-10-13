#include "scn/step/boss/mahoroabattle2/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/mahoroabattle2/AnotherDimensionType.h"
#include "scn/step/boss/mahoroabattle2/Custom.h"
#include "scn/step/boss/mahoroabattle2/EnemyCtrl.h"
#include "scn/step/boss/mahoroabattle2/KeptAbilityCtrl.h"
#include "scn/step/boss/mahoroabattle2/LaserCtrl.h"
#include "scn/step/boss/mahoroabattle2/MagicBallCtrl.h"
#include "scn/step/boss/mahoroabattle2/NeedleCtrl.h"
#include "scn/step/boss/mahoroabattle2/ScriptData.h"
#include "scn/step/boss/mahoroabattle2/StateAnotherDimension.h"
#include "scn/step/boss/mahoroabattle2/StateBlackHole.h"
#include "scn/step/boss/mahoroabattle2/StateCallingShot.h"
#include "scn/step/boss/mahoroabattle2/StateGrandMagicBall.h"
#include "scn/step/boss/mahoroabattle2/StateKillNeedleWarp.h"
#include "scn/step/boss/mahoroabattle2/StateKillNeedleWarpReady.h"
#include "scn/step/boss/mahoroabattle2/StateLaser.h"
#include "scn/step/boss/mahoroabattle2/StateLaserCharge.h"
#include "scn/step/boss/mahoroabattle2/StateMenace.h"
#include "scn/step/boss/mahoroabattle2/StateMove.h"
#include "scn/step/boss/mahoroabattle2/StateReverseDimension.h"
#include "scn/step/boss/mahoroabattle2/StateSuperBeamStart.h"
#include "scn/step/boss/mahoroabattle2/StateSuperFire.h"
#include "scn/step/boss/mahoroabattle2/StateSuperFireV.h"
#include "scn/step/boss/mahoroabattle2/StateSuperIceHammer.h"
#include "scn/step/boss/mahoroabattle2/StateSuperSword.h"
#include "scn/step/boss/mahoroabattle2/StateWarpHoleAttack.h"
#include "scn/step/boss/mahoroabattle2/StateWarpHoleAttackEnd.h"
#include "scn/step/boss/mahoroabattle2/StateWarpHoleAttackStart.h"
#include "scn/step/boss/mahoroabattle2/StateWarpHoleLaserStart.h"
#include "scn/step/boss/mahoroabattle2/StateWarpIn.h"
#include "scn/step/boss/mahoroabattle2/StateWarpOut.h"
#include "scn/step/boss/mahoroabattle2/StateWaveAttack.h"
#include "scn/step/boss/mahoroabattle2/SuperSwordCtrl.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace mahoroabattle2 {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

ScriptData& t_scriptData() {
    return t_custom().scriptData();
}

void t_SetNextState_WarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpIn, Boss*>(&MintBoss::Obj());
}

// TODO: the original passes the temporary to setNextState by value without copying it; the reference stands in
// for that (see util/StateChanger.h), here and in every state change below that names the vector as one.
void t_SetNextState_WarpOut(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpOut, Boss*, const hel::math::Vector3&>(&MintBoss::Obj(), hel::math::Vector3(x, y, z));
}

void t_SetNextState_Move(f32 x, f32 y, f32 z, int a) {
    MintBoss::Obj().stateChanger().setNextState<StateMove, Boss*, const hel::math::Vector3&, u32>(&MintBoss::Obj(), hel::math::Vector3(x, y, z), a);
}

void t_SetNextState_Menace() {
    MintBoss::Obj().stateChanger().setNextState<StateMenace, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_AnotherDimension(int type) {
    MintBoss::Obj().stateChanger().setNextState<StateAnotherDimension, Boss*, AnotherDimensionType>(
        &MintBoss::Obj(), static_cast<AnotherDimensionType>(type));
}

void t_SetNextState_WaveAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateWaveAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_CallingShot() {
    MintBoss::Obj().stateChanger().setNextState<StateCallingShot, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_GrandMagicBall() {
    MintBoss::Obj().stateChanger().setNextState<StateGrandMagicBall, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Laser() {
    MintBoss::Obj().stateChanger().setNextState<StateLaser, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_LaserCharge(f32 x, f32 y) {
    MintBoss::Obj().stateChanger().setNextState<StateLaserCharge, Boss*, hel::math::Vector2>(&MintBoss::Obj(), hel::math::Vector2(x, y));
}

void t_SetNextState_SuperBeam(int a, int b, int c, int d) {
    MintBoss::Obj().stateChanger().setNextState<StateSuperBeamStart, Boss*, u32, u32, u32, u32>(&MintBoss::Obj(), a, b, c, d);
}

void t_SetNextState_SuperFire(f32 a, f32 b, f32 c) {
    MintBoss::Obj().stateChanger().setNextState<StateSuperFire, Boss*, f32, f32, f32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_SuperFireV(f32 a, f32 b, f32 c) {
    MintBoss::Obj().stateChanger().setNextState<StateSuperFireV, Boss*, f32, f32, f32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_SuperSword() {
    MintBoss::Obj().stateChanger().setNextState<StateSuperSword, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SuperIceHammer(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateSuperIceHammer, Boss*, const hel::math::Vector3&>(&MintBoss::Obj(),
                                                                                                 hel::math::Vector3(x, y, z));
}

void t_SetNextState_BlackHole() {
    MintBoss::Obj().stateChanger().setNextState<StateBlackHole, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_KillNeedleWarpReady() {
    MintBoss::Obj().stateChanger().setNextState<StateKillNeedleWarpReady, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_KillNeedleWarp() {
    MintBoss::Obj().stateChanger().setNextState<StateKillNeedleWarp, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ReverseDimension() {
    MintBoss::Obj().stateChanger().setNextState<StateReverseDimension, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpHoleAttackStart() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttackStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpHoleAttack(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, int a) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttack, Boss*, const hel::math::Vector3&, const hel::math::Vector3&, u32>(
        &MintBoss::Obj(), hel::math::Vector3(x0, y0, z0), hel::math::Vector3(x1, y1, z1), a);
}

void t_SetNextState_WarpHoleAttackEnd(f32 x0, f32 y0, f32 z0, f32 x1, f32 y1, f32 z1, int a) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleAttackEnd, Boss*, const hel::math::Vector3&, const hel::math::Vector3&, u32>(
        &MintBoss::Obj(), hel::math::Vector3(x0, y0, z0), hel::math::Vector3(x1, y1, z1), a);
}

void t_SetNextState_WarpHoleLaserStart(f32 x, f32 y, int a) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpHoleLaserStart, Boss*, hel::math::Vector2, u32>(&MintBoss::Obj(),
                                                                                                          hel::math::Vector2(x, y), a);
}

void t_Custom_AddReqMagicBallBuff(int a, int b, int c, f32 x, f32 y) {
    MagicBallCtrl::ReqData data;
    data._0 = a;
    data._4 = b;
    data._8 = c;
    hel::math::Vector2 pos(x, y);
    data._C.x = pos.x;
    data._C.y = pos.y;
    t_custom().magicBallCtrl().addReqData(data);
}

void t_Custom_ClearReqMagicBallBuff() {
    t_custom().magicBallCtrl().clearReqData();
}

void t_Custom_RequestNeedle(f32 x0, f32 y0, f32 x1, f32 y1) {
    t_custom().needleCtrl().request(hel::math::Vector2(x0, y0), hel::math::Vector2(x1, y1));
}

void t_Custom_AddReqEnemyBuff(int a, int b) {
    EnemyCtrl::ReqData data = {a, b};
    t_custom().enemyCtrl().addReqData(data);
}

void t_Custom_ClearReqEnemyBuff() {
    t_custom().enemyCtrl().clearReqData();
}

bool t_Custom_IsExistKeptAbility() {
    return t_custom().keptAbilityCtrl().isExistData();
}

int t_Custom_PickKeptAbility() {
    return t_custom().keptAbilityCtrl().pickData();
}

void t_Custom_AddReqSuperSwordBuff(int a) {
    SuperSwordCtrl::ReqData data = {a};
    t_custom().superSwordCtrl().addReqData(data);
}

void t_Custom_ClearReqSuperSwordBuff() {
    t_custom().superSwordCtrl().clearReqData();
}

void t_Custom_ReqWarpHoleLaser(int a, f32 x0, f32 y0, f32 x1, f32 y1, int b, int c, f32 d, bool e) {
    Boss& obj1 = MintBoss::Obj();
    Boss& obj0 = MintBoss::Obj();
    t_custom().laserCtrl().request(weapon::Kind_9C, a, hel::math::Vector3(x0, y0, 0.0f) + obj0.basePos().toVector3(),
                                   hel::math::Vector3(x1, y1, 0.0f) + obj1.basePos().toVector3(), b, c, d, e);
}

void t_ScriptData_SetPrevWarpNeedleType(int type) {
    t_scriptData().setPrevWarpNeedleType(type);
}

int t_ScriptData_GetPrevWarpNeedleType() {
    return t_scriptData().getPrevWarpNeedleType();
}

void t_ScriptData_SetPrevAnotherDimensionType(int type) {
    t_scriptData().setPrevAnotherDimensionType(type);
}

int t_ScriptData_GetPrevAnotherDimensionType() {
    return t_scriptData().getPrevAnotherDimensionType();
}

void t_ScriptData_SetPrevWarpHoleLaserType(int type) {
    t_scriptData().setPrevWarpHoleLaserType(type);
}

int t_ScriptData_GetPrevWarpHoleLaserType() {
    return t_scriptData().getPrevWarpHoleLaserType();
}

void t_ScriptData_SetPrevMagicBallType(int type) {
    t_scriptData().setPrevMagicBallType(type);
}

int t_ScriptData_GetPrevMagicBallType() {
    return t_scriptData().getPrevMagicBallType();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WarpIn()", WarpIn, t_SetNextState_WarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WarpOut(float,float,float)", WarpOut, t_SetNextState_WarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void Move(float,float,float,int)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void Menace()", Menace, t_SetNextState_Menace);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void AnotherDimension(int)", AnotherDimension,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_AnotherDimension));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WaveAttack()", WaveAttack, t_SetNextState_WaveAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void CallingShot()", CallingShot, t_SetNextState_CallingShot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void GrandMagicBall()", GrandMagicBall,
                         t_SetNextState_GrandMagicBall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void Laser()", Laser, t_SetNextState_Laser);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void LaserCharge(float,float)", LaserCharge,
                         t_SetNextState_LaserCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void SuperBeam(int,int,int,int)", SuperBeam,
                         t_SetNextState_SuperBeam);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void SuperFire(float,float,float)", SuperFire,
                         t_SetNextState_SuperFire);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void SuperFireV(float,float,float)", SuperFireV,
                         t_SetNextState_SuperFireV);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void SuperSword()", SuperSword, t_SetNextState_SuperSword);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void SuperIceHammer(float,float,float)", SuperIceHammer,
                         t_SetNextState_SuperIceHammer);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void BlackHole()", BlackHole, t_SetNextState_BlackHole);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void KillNeedleWarpReady()", KillNeedleWarpReady,
                         t_SetNextState_KillNeedleWarpReady);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void KillNeedleWarp()", KillNeedleWarp,
                         t_SetNextState_KillNeedleWarp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void ReverseDimension()", ReverseDimension,
                         t_SetNextState_ReverseDimension);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WarpHoleAttackStart()", WarpHoleAttackStart,
                         t_SetNextState_WarpHoleAttackStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WarpHoleAttack(float,float,float,float,float,float,int)",
                         WarpHoleAttack, t_SetNextState_WarpHoleAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState",
                         "void WarpHoleAttackEnd(float,float,float,float,float,float,int)", WarpHoleAttackEnd,
                         t_SetNextState_WarpHoleAttackEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.SetNextState", "void WarpHoleLaserStart(float,float,int)", WarpHoleLaserStart,
                         t_SetNextState_WarpHoleLaserStart);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void AddReqMagicBallBuff(int,int,int,float,float)",
                         AddReqMagicBallBuff, t_Custom_AddReqMagicBallBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void ClearReqMagicBallBuff()", ClearReqMagicBallBuff,
                         t_Custom_ClearReqMagicBallBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void RequestNeedle(float,float,float,float)", RequestNeedle,
                         t_Custom_RequestNeedle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void AddReqEnemyBuff(int,int)", AddReqEnemyBuff,
                         t_Custom_AddReqEnemyBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void ClearReqEnemyBuff()", ClearReqEnemyBuff,
                         t_Custom_ClearReqEnemyBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "bool IsExistKeptAbility()", IsExistKeptAbility,
                         t_Custom_IsExistKeptAbility);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "int PickKeptAbility()", PickKeptAbility, t_Custom_PickKeptAbility);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void AddReqSuperSwordBuff(int)", AddReqSuperSwordBuff,
                         reinterpret_cast<void (*)(u32)>(t_Custom_AddReqSuperSwordBuff));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void ClearReqSuperSwordBuff()", ClearReqSuperSwordBuff,
                         t_Custom_ClearReqSuperSwordBuff);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.Custom", "void ReqWarpHoleLaser(int,float,float,float,float,int,int,float,bool)",
                         ReqWarpHoleLaser, t_Custom_ReqWarpHoleLaser);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "void SetPrevWarpNeedleType(int)", SetPrevWarpNeedleType,
                         reinterpret_cast<void (*)(u32)>(t_ScriptData_SetPrevWarpNeedleType));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "int GetPrevWarpNeedleType()", GetPrevWarpNeedleType,
                         t_ScriptData_GetPrevWarpNeedleType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "void SetPrevAnotherDimensionType(int)",
                         SetPrevAnotherDimensionType, reinterpret_cast<void (*)(u32)>(t_ScriptData_SetPrevAnotherDimensionType));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "int GetPrevAnotherDimensionType()", GetPrevAnotherDimensionType,
                         t_ScriptData_GetPrevAnotherDimensionType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "void SetPrevWarpHoleLaserType(int)", SetPrevWarpHoleLaserType,
                         reinterpret_cast<void (*)(u32)>(t_ScriptData_SetPrevWarpHoleLaserType));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "int GetPrevWarpHoleLaserType()", GetPrevWarpHoleLaserType,
                         t_ScriptData_GetPrevWarpHoleLaserType);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "void SetPrevMagicBallType(int)", SetPrevMagicBallType,
                         reinterpret_cast<void (*)(u32)>(t_ScriptData_SetPrevMagicBallType));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MahoroaBattle2.ScriptData", "int GetPrevMagicBallType()", GetPrevMagicBallType,
                         t_ScriptData_GetPrevMagicBallType);
}

}

}}}}  // namespace scn::step::boss::mahoroabattle2
