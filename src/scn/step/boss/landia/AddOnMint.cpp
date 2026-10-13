#include "scn/step/boss/landia/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/landia/Custom.h"
#include "scn/step/boss/landia/SingleCtrl.h"
#include "scn/step/boss/landia/SingleWeaponCtrl.h"
#include "scn/step/boss/landia/StateFireBreath.h"
#include "scn/step/boss/landia/StateGlideStart.h"
#include "scn/step/boss/landia/StateMove.h"
#include "scn/step/boss/landia/StateMoveTwinBreathContinuity.h"
#include "scn/step/boss/landia/StateSeparation.h"
#include "scn/step/boss/landia/StateTail.h"
#include "scn/step/boss/landia/StateTailEnd.h"
#include "scn/step/boss/landia/StateTailStart.h"
#include "scn/step/boss/landia/StateTwinBreath.h"
#include "scn/step/boss/landia/StateUnion.h"
#include "scn/step/boss/landia/StateWindCutter.h"
#include "scn/step/boss/landia/StateZGlide.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace landia {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Move(int kind, f32 x, f32 y) {
    StateMove::Config config;
    config._0 = kind;
    config._4 = hel::math::Vector2(x, y);
    MintBoss::Obj().stateChanger().setNextState<StateMove, Boss*, StateMove::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_FireBreath(int kind) {
    StateFireBreath::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateFireBreath, Boss*, StateFireBreath::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Glide() {
    MintBoss::Obj().stateChanger().setNextState<StateGlideStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ZGlide() {
    MintBoss::Obj().stateChanger().setNextState<StateZGlide, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_WindCutter(int kind) {
    StateWindCutter::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateWindCutter, Boss*, StateWindCutter::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_TailStart() {
    MintBoss::Obj().stateChanger().setNextState<StateTailStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Tail(int kind) {
    StateTail::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateTail, Boss*, StateTail::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_TailEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateTailEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TwinBreathCenter(int kind) {
    StateTwinBreath::Config config;
    config._0 = kind;
    MintBoss::Obj().stateChanger().setNextState<StateTwinBreath, Boss*, StateTwinBreath::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_TwinBreathContinuity() {
    StateTwinBreath::Config config;
    config._0 = 4;
    MintBoss::Obj().stateChanger().setNextState<StateTwinBreath, Boss*, StateTwinBreath::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_MoveTwinBreathContinuity(f32 time, f32 x, f32 y, bool flag) {
    StateMoveTwinBreathContinuity::Config config;
    config._0 = time;
    config._4 = hel::math::Vector2(x, y);
    config._C = flag;
    MintBoss::Obj().stateChanger().setNextState<StateMoveTwinBreathContinuity, Boss*, StateMoveTwinBreathContinuity::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Separation() {
    MintBoss::Obj().stateChanger().setNextState<StateSeparation, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Union() {
    MintBoss::Obj().stateChanger().setNextState<StateUnion, Boss*>(&MintBoss::Obj());
}

void t_SingleCtrl_Signal(int kind) {
    t_custom().singleCtrl().signal(static_cast<SignalKind>(kind));
}

bool t_SingleCtrl_FlagActionEnd() {
    return t_custom().singleCtrl().flagActionEnd();
}

void t_SingleCtrl_OnFinishFormationPass() {
    t_custom().singleCtrl().onFinishFormationPass();
    t_custom().singleWeaponCtrl().onFinishFormationPass();
}

void t_SingleCtrl_OnFinishGrandCross() {
    t_custom().singleWeaponCtrl().onFinishGrandCross();
}

void t_SingleCtrl_ReqGrandCrossNipRestart() {
    t_custom().singleCtrl().reqGrandCross(SignalKind_GrandCrossNipRestart);
}

void t_SingleCtrl_SetFireRainStarHitHeightSingleNum() {
    t_custom().singleCtrl().setFireRainStarHitHeightSingleNum();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void Move(int,float,float)", Move, t_SetNextState_Move);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void FireBreath(int)", FireBreath, t_SetNextState_FireBreath);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void Glide()", Glide, t_SetNextState_Glide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void ZGlide()", ZGlide, t_SetNextState_ZGlide);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void WindCutter(int)", WindCutter, t_SetNextState_WindCutter);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void TailStart()", TailStart, t_SetNextState_TailStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void Tail(int)", Tail, t_SetNextState_Tail);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void TailEnd()", TailEnd, t_SetNextState_TailEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void TwinBreathCenter(int)", TwinBreathCenter, t_SetNextState_TwinBreathCenter);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void TwinBreathContinuity()", TwinBreathContinuity,
                         t_SetNextState_TwinBreathContinuity);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void MoveTwinBreathContinuity(float,float,float,bool)", MoveTwinBreathContinuity,
                         t_SetNextState_MoveTwinBreathContinuity);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void Separation()", Separation, t_SetNextState_Separation);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SetNextState", "void Union()", Union, t_SetNextState_Union);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "void Signal(int)", Signal, t_SingleCtrl_Signal);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "bool FlagActionEnd()", FlagActionEnd, t_SingleCtrl_FlagActionEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "void OnFinishFormationPass()", OnFinishFormationPass,
                         t_SingleCtrl_OnFinishFormationPass);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "void OnFinishGrandCross()", OnFinishGrandCross, t_SingleCtrl_OnFinishGrandCross);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "void ReqGrandCrossNipRestart()", ReqGrandCrossNipRestart,
                         t_SingleCtrl_ReqGrandCrossNipRestart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Landia.SingleCtrl", "void SetFireRainStarHitHeightSingleNum()", SetFireRainStarHitHeightSingleNum,
                         t_SingleCtrl_SetFireRainStarHitHeightSingleNum);
}

}

}}}}  // namespace scn::step::boss::landia
