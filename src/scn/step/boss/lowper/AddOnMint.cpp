#include "scn/step/boss/lowper/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/lowper/Custom.h"
#include "scn/step/boss/lowper/DataBuff.h"
#include "scn/step/boss/lowper/ScriptKind.h"
#include "scn/step/boss/lowper/StateBarrierAttack.h"
#include "scn/step/boss/lowper/StateBombFar.h"
#include "scn/step/boss/lowper/StateBombOutInOut.h"
#include "scn/step/boss/lowper/StateBombOutOutIn.h"
#include "scn/step/boss/lowper/StateFireTackleRestart.h"
#include "scn/step/boss/lowper/StateFireTackleStart.h"
#include "scn/step/boss/lowper/StateFreezeAttackSpine.h"
#include "scn/step/boss/lowper/StateFreezeAttackStart.h"
#include "scn/step/boss/lowper/StateFreezeFallAttack.h"
#include "scn/step/boss/lowper/StateGlideShot.h"
#include "scn/step/boss/lowper/StateLaugh.h"
#include "scn/step/boss/lowper/StateMove.h"
#include "scn/step/boss/lowper/StateMoveToFar.h"
#include "scn/step/boss/lowper/StateMoveToOtherSide.h"
#include "scn/step/boss/lowper/StateRainBomb.h"
#include "scn/step/boss/lowper/StateRainBombDouble.h"
#include "scn/step/boss/lowper/StateReflectHomingShot.h"
#include "scn/step/boss/lowper/StateReqBlackHole.h"
#include "scn/step/boss/lowper/StateReverseDimension.h"
#include "scn/step/boss/lowper/StateShotBullet.h"
#include "scn/step/boss/lowper/StateShotBulletStart.h"
#include "scn/step/boss/lowper/StateSparkAttackStart.h"
#include "scn/step/boss/lowper/StateSparkShot.h"
#include "scn/step/boss/lowper/StateSprinkler.h"
#include "scn/step/boss/lowper/StateSummonBarrier.h"
#include "scn/step/boss/lowper/StateTackleFar.h"
#include "scn/step/boss/lowper/StateTackleFarRolling.h"
#include "scn/step/boss/lowper/StateTackleFarStart.h"
#include "scn/step/boss/lowper/StateTackleGlide.h"
#include "scn/step/boss/lowper/StateTackleGlideStart.h"
#include "scn/step/boss/lowper/StateTackleGround.h"
#include "scn/step/boss/lowper/StateTackleGroundPre.h"
#include "scn/step/boss/lowper/StateTackleGroundStart.h"
#include "scn/step/boss/lowper/StateVortex.h"
#include "scn/step/boss/lowper/StateWait.h"
#include "scn/step/boss/lowper/StateWarpIn.h"
#include "scn/step/boss/lowper/StateWarpOut.h"
#include "scn/step/enemy/lowperbullet/VariationKind.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace lowper {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

// TODO: the original passes the temporary to setNextState by value without copying it; the reference stands in
// for that (see util/StateChanger.h), here and in every state change below that names the vector as one.
void t_SetNextState_Wait(f32 x, f32 y) {
    MintBoss::Obj().stateChanger().setNextState<StateWait, Boss*, const Vector3&>(&MintBoss::Obj(), Vector3(x, y, 0.0f));
}

void t_SetNextState_Move(f32 x, f32 y, int a) {
    MintBoss::Obj().stateChanger().setNextState<StateMove, Boss*, const Vector3&, u32>(&MintBoss::Obj(),
                                                                                Vector3(x, y, 0.0f), a);
}

void t_SetNextState_MoveToFar(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateMoveToFar, Boss*, f32>(&MintBoss::Obj(), a);
}

void t_SetNextState_MoveToOtherSide() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveToOtherSide, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ShotBulletStart(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBulletStart, Boss*, f32>(&MintBoss::Obj(), a);
}

void t_SetNextState_ShotBullet(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBullet, a, enemy::lowperbullet::VariationKind_Normal, 0);
}

void t_SetNextState_ShotBulletFast(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBulletFast, a, enemy::lowperbullet::VariationKind_Normal, 0);
}

void t_SetNextState_ShotBulletHoming(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBullet, a, enemy::lowperbullet::VariationKind_Homing, 0);
}

void t_SetNextState_ShotBulletHomingFast(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBulletFast, a, enemy::lowperbullet::VariationKind_Homing, 0);
}

void t_SetNextState_ShotBulletHoming2(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBullet, a, enemy::lowperbullet::VariationKind_Homing2, 0);
}

void t_SetNextState_ShotBulletHoming2Fast(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, int>(
        &MintBoss::Obj(), ScriptKind_ShotBulletFast, a, enemy::lowperbullet::VariationKind_Homing2, 0);
}

void t_SetNextState_ShotBulletStill(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, u32>(
        &MintBoss::Obj(), ScriptKind_ShotBullet, 0.0f, enemy::lowperbullet::VariationKind_Still, a);
}

void t_SetNextState_ShotBulletStillFast(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32, enemy::lowperbullet::VariationKind, u32>(
        &MintBoss::Obj(), ScriptKind_ShotBulletFast, 0.0f, enemy::lowperbullet::VariationKind_Still, a);
}

void t_SetNextState_BombOutOutIn() {
    MintBoss::Obj().stateChanger().setNextState<StateBombOutOutIn, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BombOutInOut() {
    MintBoss::Obj().stateChanger().setNextState<StateBombOutInOut, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BombFar() {
    MintBoss::Obj().stateChanger().setNextState<StateBombFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TackleGlideStart() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleGlideStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TackleGlide(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateTackleGlide, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_TackleGroundStart() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleGroundStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TackleGround(int a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateTackleGround, Boss*, u32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_TackleGroundPre(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateTackleGroundPre, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_TackleFarStart() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleFarStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TackleFar() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TackleFarRolling() {
    MintBoss::Obj().stateChanger().setNextState<StateTackleFarRolling, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Sprinkler() {
    MintBoss::Obj().stateChanger().setNextState<StateSprinkler, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_RainBomb(f32 x, f32 y, int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateRainBomb, Boss*, const Vector3&, u32, u32, u32>(
        &MintBoss::Obj(), Vector3(x, y, 0.0f), a, b, c);
}

void t_SetNextState_RainBombDouble(f32 x, f32 y, int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateRainBombDouble, Boss*, const Vector3&, u32, u32, u32>(
        &MintBoss::Obj(), Vector3(x, y, 0.0f), a, b, c);
}

void t_SetNextState_SummonBarrier() {
    MintBoss::Obj().stateChanger().setNextState<StateSummonBarrier, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpIn, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WarpOut(f32 x, f32 y) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpOut, Boss*, const Vector3&>(&MintBoss::Obj(),
                                                                              Vector3(x, y, 0.0f));
}

void t_SetNextState_Laugh() {
    MintBoss::Obj().stateChanger().setNextState<StateLaugh, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_FireTackle(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateFireTackleStart, Boss*, u32, u32, bool>(&MintBoss::Obj(), a, b, false);
}

void t_SetNextState_FireTackleExFirst(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateFireTackleStart, Boss*, u32, u32, bool>(&MintBoss::Obj(), a, b, true);
}

void t_SetNextState_FireTackleExSecond(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateFireTackleRestart, Boss*, u32, u32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_SparkAttack(int a, int b, f32 c) {
    MintBoss::Obj().stateChanger().setNextState<StateSparkAttackStart, Boss*, u32, u32, f32, bool>(&MintBoss::Obj(), a, b, c, false);
}

void t_SetNextState_SparkAttackRolling(int a, int b, f32 c) {
    MintBoss::Obj().stateChanger().setNextState<StateSparkAttackStart, Boss*, u32, u32, f32, bool>(&MintBoss::Obj(), a, b, c, true);
}

void t_SetNextState_FreezeAttack(int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateFreezeAttackStart, Boss*, u32, u32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_FreezeFallAttack(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateFreezeFallAttack, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_FreezeAttackSpine(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateFreezeAttackSpine, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_Vortex() {
    MintBoss::Obj().stateChanger().setNextState<StateVortex, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SparkShot() {
    MintBoss::Obj().stateChanger().setNextState<StateSparkShot, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BarrierAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateBarrierAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ReflectHomingShot() {
    MintBoss::Obj().stateChanger().setNextState<StateReflectHomingShot, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_GlideShot(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateGlideShot, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_ReqBlackHole(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateReqBlackHole, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_ReverseWorld() {
    MintBoss::Obj().stateChanger().setNextState<StateReverseDimension, Boss*>(&MintBoss::Obj());
}

int t_Custom_GetBarrierCount() {
    return t_custom().enemyCtrl().getBarrierCount();
}

bool t_Custom_CanSetBlackHole(f32 a) {
    return t_custom().miniBlackHoleCtrl().canSetBlackHole(a);
}

void t_DataBuff_AddSprinklerBulletSpeedData(f32 speed) {
    t_custom().dataBuff().addSprinklerBulletSpeedData(speed);
}

void t_DataBuff_AddBombFarBulletData(f32 a, int b) {
    DataBuff::BombFarBulletData data = {a, b};
    t_custom().dataBuff().addBombFarBulletData(data);
}

void t_DataBuff_AddVortexBulletSpeedData(f32 speed) {
    t_custom().dataBuff().addVortexBulletSpeedData(speed);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void MoveToFar(float)", MoveToFar, t_SetNextState_MoveToFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void MoveToOtherSide()", MoveToOtherSide, t_SetNextState_MoveToOtherSide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletStart(float)", ShotBulletStart,
                         t_SetNextState_ShotBulletStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBullet(float)", ShotBullet, t_SetNextState_ShotBullet);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletFast(float)", ShotBulletFast,
                         t_SetNextState_ShotBulletFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletHoming(float)", ShotBulletHoming,
                         t_SetNextState_ShotBulletHoming);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletHomingFast(float)", ShotBulletHomingFast,
                         t_SetNextState_ShotBulletHomingFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletHoming2(float)", ShotBulletHoming2,
                         t_SetNextState_ShotBulletHoming2);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletHoming2Fast(float)", ShotBulletHoming2Fast,
                         t_SetNextState_ShotBulletHoming2Fast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletStill(int)", ShotBulletStill,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_ShotBulletStill));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ShotBulletStillFast(int)", ShotBulletStillFast,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_ShotBulletStillFast));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void BombOutOutIn()", BombOutOutIn, t_SetNextState_BombOutOutIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void BombOutInOut()", BombOutInOut, t_SetNextState_BombOutInOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void BombFar()", BombFar, t_SetNextState_BombFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleGlideStart()", TackleGlideStart,
                         t_SetNextState_TackleGlideStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleGlide(int)", TackleGlide,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_TackleGlide));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleGroundStart()", TackleGroundStart,
                         t_SetNextState_TackleGroundStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleGround(int,float)", TackleGround,
                         t_SetNextState_TackleGround);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleGroundPre(int)", TackleGroundPre,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_TackleGroundPre));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleFarStart()", TackleFarStart, t_SetNextState_TackleFarStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleFar()", TackleFar, t_SetNextState_TackleFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void TackleFarRolling()", TackleFarRolling,
                         t_SetNextState_TackleFarRolling);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void Wait(float,float)", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void Move(float,float,int)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void Sprinkler()", Sprinkler, t_SetNextState_Sprinkler);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void RainBomb(float,float,int,int,int)", RainBomb,
                         t_SetNextState_RainBomb);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void RainBombDouble(float,float,int,int,int)", RainBombDouble,
                         t_SetNextState_RainBombDouble);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void SummonBarrier()", SummonBarrier, t_SetNextState_SummonBarrier);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void WarpIn()", WarpIn, t_SetNextState_WarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void WarpOut(float,float)", WarpOut, t_SetNextState_WarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void Laugh()", Laugh, t_SetNextState_Laugh);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FireTackle(int,int)", FireTackle, t_SetNextState_FireTackle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FireTackleExFirst(int,int)", FireTackleExFirst,
                         t_SetNextState_FireTackleExFirst);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FireTackleExSecond(int,int)", FireTackleExSecond,
                         t_SetNextState_FireTackleExSecond);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void SparkAttack(int,int,float)", SparkAttack,
                         t_SetNextState_SparkAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void SparkAttackRolling(int,int,float)", SparkAttackRolling,
                         t_SetNextState_SparkAttackRolling);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FreezeAttack(int,int,int)", FreezeAttack,
                         t_SetNextState_FreezeAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FreezeFallAttack(int)", FreezeFallAttack,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_FreezeFallAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void FreezeAttackSpine(int)", FreezeAttackSpine,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_FreezeAttackSpine));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void Vortex()", Vortex, t_SetNextState_Vortex);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void SparkShot()", SparkShot, t_SetNextState_SparkShot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void BarrierAttack()", BarrierAttack, t_SetNextState_BarrierAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ReflectHomingShot()", ReflectHomingShot,
                         t_SetNextState_ReflectHomingShot);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void GlideShot(int)", GlideShot,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_GlideShot));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ReqBlackHole(int)", ReqBlackHole,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_ReqBlackHole));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.SetNextState", "void ReverseWorld()", ReverseWorld, t_SetNextState_ReverseWorld);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.Custom", "int GetBarrierCount()", GetBarrierCount, t_Custom_GetBarrierCount);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.Custom", "bool CanSetBlackHole(float)", CanSetBlackHole, t_Custom_CanSetBlackHole);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.DataBuff", "void AddSprinklerBulletSpeedData(float)", AddSprinklerBulletSpeedData,
                         t_DataBuff_AddSprinklerBulletSpeedData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.DataBuff", "void AddBombFarBulletData(float,int)", AddBombFarBulletData,
                         t_DataBuff_AddBombFarBulletData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Lowper.DataBuff", "void AddVortexBulletSpeedData(float)", AddVortexBulletSpeedData,
                         t_DataBuff_AddVortexBulletSpeedData);
}

}

}}}}  // namespace scn::step::boss::lowper
