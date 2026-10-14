#include "scn/step/boss/goliath/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/goliath/BlizzardDesc.h"
#include "scn/step/boss/goliath/Custom.h"
#include "scn/step/boss/goliath/EnemyCtrl.h"
#include "scn/step/boss/goliath/LandCtrl.h"
#include "scn/step/boss/goliath/StateBlizzardStart.h"
#include "scn/step/boss/goliath/StateEnergyBallStart.h"
#include "scn/step/boss/goliath/StateFallIcicleStart.h"
#include "scn/step/boss/goliath/StateGroundPunch.h"
#include "scn/step/boss/goliath/StateJumpFarHeroStart.h"
#include "scn/step/boss/goliath/StatePunchCharge.h"
#include "scn/step/boss/goliath/StateRocket.h"
#include "scn/step/boss/goliath/StateRocketAttack.h"
#include "scn/step/boss/goliath/StateRocketCharge.h"
#include "scn/step/boss/goliath/StateSwoopStart.h"
#include "scn/step/boss/goliath/StateWallClimb.h"
#include "scn/step/boss/goliath/StateWallJumpFarHeroStart.h"
#include "scn/step/boss/goliath/StateWallJumpStart.h"
#include "scn/step/boss/goliath/StateWallThrow.h"

using hel::common::DynamicCastToRef;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Punch(int _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StatePunchCharge, Boss*, u32, u32, bool>(&MintBoss::Obj(), _0, _1, true);
}

void t_SetNextState_PunchNoFinish(int _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StatePunchCharge, Boss*, u32, u32, bool>(&MintBoss::Obj(), _0, _1, false);
}

void t_SetNextState_WallJump(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateWallJumpStart, Boss*, f32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_WallJumpFarHero(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateWallJumpFarHeroStart, Boss*, f32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_WallClimb(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateWallClimb, Boss*, f32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_WallThrow() {
    MintBoss::Obj().stateChanger().setNextState<StateWallThrow, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Swoop(int _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateSwoopStart, Boss*, u32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_GroundPunch() {
    MintBoss::Obj().stateChanger().setNextState<StateGroundPunch, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Blizzard(int time, f32 _1, f32 _2, f32 _3) {
    BlizzardDesc desc;
    desc._0 = _1;
    desc._4 = _2;
    desc._8 = _3;
    desc._C = 0.0f;
    desc._10 = false;
    MintBoss::Obj().stateChanger().setNextState<StateBlizzardStart, Boss*, u32, BlizzardDesc>(&MintBoss::Obj(), time, desc);
}

void t_SetNextState_BlizzardEx(int time, f32 _1, f32 _2, f32 _3, f32 _4) {
    BlizzardDesc desc;
    desc._0 = _1;
    desc._4 = _2;
    desc._8 = _3;
    desc._C = _4;
    desc._10 = true;
    MintBoss::Obj().stateChanger().setNextState<StateBlizzardStart, Boss*, u32, BlizzardDesc>(&MintBoss::Obj(), time, desc);
}

void t_SetNextState_JumpFarHero(int _0, f32 _1) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpFarHeroStart, Boss*, u32, f32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_Rocket(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateRocket, Boss*, f32, u32, bool>(&MintBoss::Obj(), _0, _1, true);
}

void t_SetNextState_RocketToFront(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateRocket, Boss*, f32, u32, bool>(&MintBoss::Obj(), _0, _1, false);
}

void t_SetNextState_RocketAttack(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateRocketAttack, Boss*, f32, u32, bool>(&MintBoss::Obj(), _0, _1, true);
}

void t_SetNextState_RocketAttackReflect(f32 _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateRocketAttack, Boss*, f32, u32, bool>(&MintBoss::Obj(), _0, _1, false);
}

void t_SetNextState_RocketCharge() {
    MintBoss::Obj().stateChanger().setNextState<StateRocketCharge, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_FallIcicle(int _0, int _1) {
    MintBoss::Obj().stateChanger().setNextState<StateFallIcicleStart, Boss*, u32, u32>(&MintBoss::Obj(), _0, _1);
}

void t_SetNextState_EnergyBall(int _0, int _1, f32 _2) {
    MintBoss::Obj().stateChanger().setNextState<StateEnergyBallStart, Boss*, u32, u32, f32>(&MintBoss::Obj(), _0, _1, _2);
}

void t_EnemyCtrl_AddReqData(int _0, f32 _1, f32 _2, bool _3) {
    EnemyCtrl::ReqData data;
    data._0 = _0;
    data._4 = _1;
    data._8 = _2;
    data._C = _3;
    data._D = false;
    t_custom().enemyCtrl().addReqData(data);
}

void t_EnemyCtrl_AddReqData_AimHero(int _0, f32 _1, bool _3) {
    EnemyCtrl::ReqData data;
    data._0 = _0;
    data._4 = _1;
    data._8 = 0.0f;
    data._C = _3;
    data._D = true;
    t_custom().enemyCtrl().addReqData(data);
}

void t_EnemyCtrl_ClearReqBuff() {
    t_custom().enemyCtrl().clearReqBuff();
}

int t_LandCtrl_GetLevel() {
    return t_custom().landCtrl().getLevel();
}

int t_LandCtrl_GetMaxLevelOnBattle() {
    return t_custom().landCtrl().getMaxLevelOnBattle();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void Punch(int,int)", Punch, t_SetNextState_Punch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void PunchNoFinish(int,int)", PunchNoFinish, t_SetNextState_PunchNoFinish);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void WallJump(float,int)", WallJump, t_SetNextState_WallJump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void WallJumpFarHero(float,int)", WallJumpFarHero, t_SetNextState_WallJumpFarHero);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void WallClimb(float,int)", WallClimb, t_SetNextState_WallClimb);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void WallThrow()", WallThrow, t_SetNextState_WallThrow);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void Swoop(int,int)", Swoop, t_SetNextState_Swoop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void GroundPunch()", GroundPunch, t_SetNextState_GroundPunch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void Blizzard(int,float,float,float)", Blizzard, t_SetNextState_Blizzard);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void BlizzardEx(int,float,float,float,float)", BlizzardEx, t_SetNextState_BlizzardEx);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void JumpFarHero(int,float)", JumpFarHero, t_SetNextState_JumpFarHero);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void Rocket(float,int)", Rocket, t_SetNextState_Rocket);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void RocketToFront(float,int)", RocketToFront, t_SetNextState_RocketToFront);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void RocketAttack(float,int)", RocketAttack, t_SetNextState_RocketAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void RocketAttackReflect(float,int)", RocketAttackReflect,
                         t_SetNextState_RocketAttackReflect);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void RocketCharge()", RocketCharge, t_SetNextState_RocketCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void FallIcicle(int,int)", FallIcicle, t_SetNextState_FallIcicle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.SetNextState", "void EnergyBall(int,int,float)", EnergyBall, t_SetNextState_EnergyBall);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.EnemyCtrl", "void AddReqData(int,float,float,bool)", AddReqData, t_EnemyCtrl_AddReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.EnemyCtrl", "void AddReqDataAimHero(int,float,bool)", AddReqDataAimHero,
                         t_EnemyCtrl_AddReqData_AimHero);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.EnemyCtrl", "void ClearReqBuff()", ClearReqBuff, t_EnemyCtrl_ClearReqBuff);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.LandCtrl", "int GetLevel()", GetLevel, t_LandCtrl_GetLevel);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Goliath.LandCtrl", "int GetMaxLevelOnBattle()", GetMaxLevelOnBattle, t_LandCtrl_GetMaxLevelOnBattle);
}

}

}}}}  // namespace scn::step::boss::goliath
