#include "scn/step/boss/grandlowper/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/grandlowper/CoverCtrl.h"
#include "scn/step/boss/grandlowper/Custom.h"
#include "scn/step/boss/grandlowper/EnemyGenCtrl.h"
#include "scn/step/boss/grandlowper/ScriptKind.h"
#include "scn/step/boss/grandlowper/StateBoundPound.h"
#include "scn/step/boss/grandlowper/StateBoundPoundFinish.h"
#include "scn/step/boss/grandlowper/StateCoveredWait.h"
#include "scn/step/boss/grandlowper/StateCoveredWarpIn.h"
#include "scn/step/boss/grandlowper/StateCoveredWarpOut.h"
#include "scn/step/boss/grandlowper/StateDeadlyBallReady.h"
#include "scn/step/boss/grandlowper/StateDimensionSearch.h"
#include "scn/step/boss/grandlowper/StateDimensionTackle.h"
#include "scn/step/boss/grandlowper/StateDimensionTackleExtra.h"
#include "scn/step/boss/grandlowper/StateFireTackleStart.h"
#include "scn/step/boss/grandlowper/StateFlyingBomb.h"
#include "scn/step/boss/grandlowper/StateFreezeAttackStart.h"
#include "scn/step/boss/grandlowper/StateGlideAttack.h"
#include "scn/step/boss/grandlowper/StateGlideAttackFar.h"
#include "scn/step/boss/grandlowper/StateHealChargeStart.h"
#include "scn/step/boss/grandlowper/StateHomingShot.h"
#include "scn/step/boss/grandlowper/StateMenace.h"
#include "scn/step/boss/grandlowper/StateMoveToFar.h"
#include "scn/step/boss/grandlowper/StateShotBullet.h"
#include "scn/step/boss/grandlowper/StateShotBulletFar.h"
#include "scn/step/boss/grandlowper/StateWait.h"
#include "scn/step/boss/grandlowper/StateWaitLow.h"
#include "scn/step/boss/grandlowper/StateWarpIn.h"
#include "scn/step/boss/grandlowper/StateWarpOut.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace grandlowper {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Wait() {
    MintBoss::Obj().stateChanger().setNextState<StateWait, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WaitLow() {
    MintBoss::Obj().stateChanger().setNextState<StateWaitLow, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_GlideAttack(int _0, f32 _1, f32 _2, f32 _3, f32 _4) {
    StateGlideAttack::Desc desc;
    desc._0 = _0;
    desc._4 = _1;
    desc._8 = _2;
    desc._C = _3;
    desc._10 = _4;
    MintBoss::Obj().stateChanger().setNextState<StateGlideAttack, Boss*, StateGlideAttack::Desc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_Menace() {
    MintBoss::Obj().stateChanger().setNextState<StateMenace, Boss*, bool>(&MintBoss::Obj(), false);
}

void t_SetNextState_MenaceMoveCenter() {
    MintBoss::Obj().stateChanger().setNextState<StateMenace, Boss*, bool>(&MintBoss::Obj(), true);
}

void t_SetNextState_ShotBullet(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32>(&MintBoss::Obj(), ScriptKind_ShotBullet, _0);
}

void t_SetNextState_ShotBulletFast(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32>(&MintBoss::Obj(), ScriptKind_ShotBulletFast, _0);
}

void t_SetNextState_ShotBulletVeryFast(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32>(&MintBoss::Obj(), ScriptKind_ShotBulletVeryFast, _0);
}

void t_SetNextState_ShotBulletFastest(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateShotBullet, Boss*, ScriptKind, f32>(&MintBoss::Obj(), ScriptKind_ShotBulletFastest, _0);
}

void t_SetNextState_WarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateWarpIn, Boss*>(&MintBoss::Obj());
}

// TODO: the original passes the temporary to setNextState by value without copying it; the reference stands in
// for that (see util/StateChanger.h), here and in every state change below that names the vector as one.
void t_SetNextState_WarpOut(f32 x, f32 y, f32 z, bool _3) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpOut, Boss*, const hel::math::Vector3&, bool>(&MintBoss::Obj(), hel::math::Vector3(x, y, z), _3);
}

void t_SetNextState_WarpOutSpMove(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateWarpOut, Boss*, const hel::math::Vector3&, bool, bool>(&MintBoss::Obj(), hel::math::Vector3(x, y, z), false, true);
}

void t_SetNextState_DimensionSearch() {
    MintBoss::Obj().stateChanger().setNextState<StateDimensionSearch, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_DimensionTackle() {
    MintBoss::Obj().stateChanger().setNextState<StateDimensionTackle, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_DimensionTackleExtra(int _0) {
    MintBoss::Obj().stateChanger().setNextState<StateDimensionTackleExtra, Boss*, u32>(&MintBoss::Obj(), _0);
}

void t_SetNextState_FlyingBomb(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateFlyingBomb, Boss*, f32, ScriptKind, bool>(&MintBoss::Obj(), _0, ScriptKind_FlyingBomb, false);
}

void t_SetNextState_FlyingDivideBomb(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateFlyingBomb, Boss*, f32, ScriptKind, bool>(&MintBoss::Obj(), _0, ScriptKind_FlyingBomb, true);
}

void t_SetNextState_FlyingBombEnd(f32 _0) {
    MintBoss::Obj().stateChanger().setNextState<StateFlyingBomb, Boss*, f32, ScriptKind, bool>(&MintBoss::Obj(), _0, ScriptKind_FlyingBombEnd, false);
}

void t_SetNextState_MoveToFar() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveToFar, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ShotBulletFar(f32 x, f32 y, bool _2) {
    hel::math::Vector3 pos(x, y, 0.5f);
    MintBoss::Obj().stateChanger().setNextState<StateShotBulletFar, Boss*, hel::math::Vector3, bool>(&MintBoss::Obj(), pos, _2);
}

void t_SetNextState_HomingShot(int _0) {
    MintBoss::Obj().stateChanger().setNextState<StateHomingShot, Boss*, u32>(&MintBoss::Obj(), _0);
}

void t_SetNextState_GlideAttackFar(int _0) {
    MintBoss::Obj().stateChanger().setNextState<StateGlideAttackFar, Boss*, u32>(&MintBoss::Obj(), _0);
}

void t_SetNextState_FireTackle(int _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateFireTackleStart, Boss*, u32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_FreezeAttack(f32 x, f32 y, int _2) {
    hel::math::Vector3 pos(x, y, 0.0f);
    MintBoss::Obj().stateChanger().setNextState<StateFreezeAttackStart, Boss*, hel::math::Vector3, u32>(&MintBoss::Obj(), pos, _2);
}

void t_SetNextState_CoveredWait() {
    MintBoss::Obj().stateChanger().setNextState<StateCoveredWait, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_CoveredWarpIn() {
    MintBoss::Obj().stateChanger().setNextState<StateCoveredWarpIn, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_CoveredWarpOut(f32 x, f32 y, f32 z) {
    MintBoss::Obj().stateChanger().setNextState<StateCoveredWarpOut, Boss*, const hel::math::Vector3&>(&MintBoss::Obj(), hel::math::Vector3(x, y, z));
}

void t_SetNextState_Heal() {
    MintBoss::Obj().stateChanger().setNextState<StateHealChargeStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BoundPound(int _0, f32 _1, f32 _2, f32 _3, f32 _4, f32 _5, f32 _6) {
    StateBoundPound::Desc desc;
    desc._0 = _0;
    desc._4 = _1;
    desc._8 = _2;
    desc._C = _3;
    desc._10 = _4;
    desc._14 = _5;
    desc._18 = _6;
    MintBoss::Obj().stateChanger().setNextState<StateBoundPound, Boss*, StateBoundPound::Desc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_BoundPoundFinish(int _0, int _1, f32 _2, f32 _3, f32 _4, f32 _5, f32 _6, f32 _7) {
    StateBoundPoundFinish::Desc desc;
    desc._0 = _0;
    desc._4 = _1;
    desc._8 = _2;
    desc._C = _3;
    desc._10 = _4;
    desc._14 = _5;
    desc._18 = _6;
    desc._1C = _7;
    MintBoss::Obj().stateChanger().setNextState<StateBoundPoundFinish, Boss*, StateBoundPoundFinish::Desc>(&MintBoss::Obj(), desc);
}

void t_SetNextState_DeadlyBallR(int _0) {
    MintBoss::Obj().stateChanger().setNextState<StateDeadlyBallReady, Boss*, bool, u32>(&MintBoss::Obj(), true, _0);
}

void t_SetNextState_DeadlyBallL(int _0) {
    MintBoss::Obj().stateChanger().setNextState<StateDeadlyBallReady, Boss*, bool, u32>(&MintBoss::Obj(), false, _0);
}

void t_Custom_AddEnemyReqData(int kind, bool _1) {
    t_custom().enemyGenCtrl().addReqData(static_cast<map::BinEnemyKind>(kind), _1);
}

void t_Custom_ClearEnemyReqData() {
    t_custom().enemyGenCtrl().clearReqData();
}

void t_Custom_ShuffleEnemyReqData() {
    t_custom().enemyGenCtrl().shuffleReqData();
}

int t_Custom_GetCoverHp() {
    return t_custom().coverCtrl().getCoverHp();
}

bool t_Custom_IsCoverHpMax() {
    return t_custom().coverCtrl().isCoverHpMax();
}

bool t_Custom_IsCoverFirstChange() {
    return t_custom().coverCtrl().isFirstChange();
}

void t_Custom_InitCover() {
    t_custom().coverCtrl().init();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void Wait()", Wait, t_SetNextState_Wait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void WaitLow()", WaitLow, t_SetNextState_WaitLow);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void GlideAttack(int,float,float,float,float)", GlideAttack,
                         t_SetNextState_GlideAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void Menace()", Menace, t_SetNextState_Menace);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void MenaceMoveCenter()", MenaceMoveCenter,
                         t_SetNextState_MenaceMoveCenter);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void ShotBullet(float)", ShotBullet, t_SetNextState_ShotBullet);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void ShotBulletFast(float)", ShotBulletFast, t_SetNextState_ShotBulletFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void ShotBulletVeryFast(float)", ShotBulletVeryFast,
                         t_SetNextState_ShotBulletVeryFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void ShotBulletFastest(float)", ShotBulletFastest,
                         t_SetNextState_ShotBulletFastest);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void WarpIn()", WarpIn, t_SetNextState_WarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void WarpOut(float,float,float,bool)", WarpOut, t_SetNextState_WarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void WarpOutSpMove(float,float,float)", WarpOutSpMove,
                         t_SetNextState_WarpOutSpMove);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void DimensionSearch()", DimensionSearch, t_SetNextState_DimensionSearch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void DimensionTackle()", DimensionTackle, t_SetNextState_DimensionTackle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void DimensionTackleExtra(int)", DimensionTackleExtra,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_DimensionTackleExtra));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void FlyingBomb(float)", FlyingBomb, t_SetNextState_FlyingBomb);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void FlyingDivideBomb(float)", FlyingDivideBomb,
                         t_SetNextState_FlyingDivideBomb);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void FlyingBombEnd(float)", FlyingBombEnd, t_SetNextState_FlyingBombEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void MoveToFar()", MoveToFar, t_SetNextState_MoveToFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void ShotBulletFar(float,float,bool)", ShotBulletFar,
                         t_SetNextState_ShotBulletFar);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void HomingShot(int)", HomingShot,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_HomingShot));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void GlideAttackFar(int)", GlideAttackFar,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_GlideAttackFar));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void FireTackle(int,int)", FireTackle, t_SetNextState_FireTackle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void FreezeAttack(float,float,int)", FreezeAttack,
                         t_SetNextState_FreezeAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void CoveredWait()", CoveredWait, t_SetNextState_CoveredWait);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void CoveredWarpIn()", CoveredWarpIn, t_SetNextState_CoveredWarpIn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void CoveredWarpOut(float,float,float)", CoveredWarpOut,
                         t_SetNextState_CoveredWarpOut);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void Heal()", Heal, t_SetNextState_Heal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void BoundPound(int,float,float,float,float,float,float)", BoundPound,
                         t_SetNextState_BoundPound);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void BoundPoundFinish(int,int,float,float,float,float,float,float)", BoundPoundFinish,
                         t_SetNextState_BoundPoundFinish);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void DeadlyBallR(int)", DeadlyBallR,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_DeadlyBallR));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.SetNextState", "void DeadlyBallL(int)", DeadlyBallL,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_DeadlyBallL));

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "void AddEnemyReqData(int,bool)", AddEnemyReqData, t_Custom_AddEnemyReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "void ClearEnemyReqData()", ClearEnemyReqData, t_Custom_ClearEnemyReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "void ShuffleEnemyReqData()", ShuffleEnemyReqData, t_Custom_ShuffleEnemyReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "int GetCoverHp()", GetCoverHp, t_Custom_GetCoverHp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "bool IsCoverHpMax()", IsCoverHpMax, t_Custom_IsCoverHpMax);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "bool IsCoverFirstChange()", IsCoverFirstChange, t_Custom_IsCoverFirstChange);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GrandLowper.Custom", "void InitCover()", InitCover, t_Custom_InitCover);
}

}

}}}}  // namespace scn::step::boss::grandlowper
