#include "scn/step/boss/doubter/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/doubter/CaptureCtrl.h"
#include "scn/step/boss/doubter/Custom.h"
#include "scn/step/boss/doubter/JugglingCtrl.h"
#include "scn/step/boss/doubter/PunchCtrl.h"
#include "scn/step/boss/doubter/ScriptKind.h"
#include "scn/step/boss/doubter/StateBoundStart.h"
#include "scn/step/boss/doubter/StateCatchSearch.h"
#include "scn/step/boss/doubter/StateEtherJumpLanding.h"
#include "scn/step/boss/doubter/StateEtherJumpRestart.h"
#include "scn/step/boss/doubter/StateEtherJumpStart.h"
#include "scn/step/boss/doubter/StateJugglingAttack.h"
#include "scn/step/boss/doubter/StateJugglingAttack2.h"
#include "scn/step/boss/doubter/StateJugglingStart.h"
#include "scn/step/boss/doubter/StateJumpCenterStart.h"
#include "scn/step/boss/doubter/StateJumpStart.h"
#include "scn/step/boss/doubter/StatePunch.h"
#include "scn/step/boss/doubter/StateSummon.h"
#include "scn/step/boss/doubter/StateTornadoChase.h"
#include "scn/step/boss/doubter/StateTornadoFall.h"
#include "scn/step/boss/doubter/StateTornadoRise.h"
#include "scn/step/boss/doubter/StateTornadoSearch.h"
#include "scn/step/boss/doubter/StateTornadoSearchCharge.h"
#include "scn/step/boss/doubter/StateTornadoStart.h"
#include "scn/step/map/BinEnemySize.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace doubter {

namespace {

Custom& t_custom() {
    return hel::common::DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Bound(f32 x, f32 y, int kind) {
    MintBoss::Obj().stateChanger().setNextState<StateBoundStart, Boss*, hel::math::Vector2, u32>(&MintBoss::Obj(),
                                                                                                 hel::math::Vector2(x, y), kind);
}

void t_SetNextState_Jump(f32 x, f32 y, int kind) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpStart, Boss*, hel::math::Vector2, u32>(&MintBoss::Obj(),
                                                                                                hel::math::Vector2(x, y), kind);
}

void t_SetNextState_JumpCenter(f32 speed, int kind) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpCenterStart, Boss*, f32, u32>(&MintBoss::Obj(), speed, kind);
}

void t_SetNextState_TornadoStart() {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TornadoRise() {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoRise, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TornadoFall() {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoFall, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_TornadoSearch(int a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoSearch, Boss*, u32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_TornadoSearchWithCharge(int a, int b, f32 c) {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoSearchCharge, Boss*, u32, u32, f32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_TornadoChase(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoChase, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_Summon(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateSummon, Boss*, u32, u32, map::BinEnemySize>(&MintBoss::Obj(), a, b,
                                                                                                 map::BinEnemySize_Normal);
}

void t_SetNextState_SummonBig(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateSummon, Boss*, u32, u32, map::BinEnemySize>(&MintBoss::Obj(), a, b,
                                                                                                 map::BinEnemySize_Big);
}

void t_SetNextState_SummonGigant(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateSummon, Boss*, u32, u32, map::BinEnemySize>(&MintBoss::Obj(), a, b,
                                                                                                 map::BinEnemySize_Gigant);
}

void t_SetNextState_Punch() {
    MintBoss::Obj().stateChanger().setNextState<StatePunch, Boss*, ScriptKind>(&MintBoss::Obj(), ScriptKind_Punch);
}

void t_SetNextState_TriplePunch() {
    MintBoss::Obj().stateChanger().setNextState<StatePunch, Boss*, ScriptKind>(&MintBoss::Obj(), ScriptKind_TriplePunch);
}

void t_SetNextState_Catch(int a, int b) {
    MintBoss::Obj().stateChanger().setNextState<StateCatchSearch, Boss*, u32, u32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_EtherJumpStart(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateEtherJumpStart, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_EtherJumpRestart(int a) {
    MintBoss::Obj().stateChanger().setNextState<StateEtherJumpRestart, Boss*, u32>(&MintBoss::Obj(), a);
}

void t_SetNextState_EtherJumpLanding() {
    MintBoss::Obj().stateChanger().setNextState<StateEtherJumpLanding, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Juggling() {
    MintBoss::Obj().stateChanger().setNextState<StateJugglingStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_JugglingAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateJugglingAttack, Boss*, StateJugglingAttack::JugglingShotKind>(
        &MintBoss::Obj(), StateJugglingAttack::JugglingShotKind_Normal);
}

void t_SetNextState_JugglingAttackFast() {
    MintBoss::Obj().stateChanger().setNextState<StateJugglingAttack, Boss*, StateJugglingAttack::JugglingShotKind>(
        &MintBoss::Obj(), StateJugglingAttack::JugglingShotKind_Fast);
}

void t_SetNextState_JugglingAttackSearch() {
    MintBoss::Obj().stateChanger().setNextState<StateJugglingAttack, Boss*, StateJugglingAttack::JugglingShotKind>(
        &MintBoss::Obj(), StateJugglingAttack::JugglingShotKind_Search);
}

void t_SetNextState_JugglingAttack2() {
    MintBoss::Obj().stateChanger().setNextState<StateJugglingAttack2, Boss*>(&MintBoss::Obj());
}

void t_Custom_PunchR_Start(f32 speed, int kind) {
    t_custom().punchCtrlR().start(speed, kind);
}

void t_Custom_PunchL_Start(f32 speed, int kind) {
    t_custom().punchCtrlL().start(speed, kind);
}

void t_Custom_Juggling_AddReqData(int a) {
    JugglingCtrl::ReqData data = {a};
    t_custom().jugglingCtrl().addReqData(data);
}

void t_Custom_Juggling_ClearReqData() {
    t_custom().jugglingCtrl().clearReqData();
}

bool t_Custom_Juggling_IsActive() {
    return t_custom().jugglingCtrl().isActive();
}

bool t_Custom_Juggling_IsHold() {
    bool hold = false;
    if (t_custom().jugglingCtrl().isHoldEnemy() || t_custom().jugglingCtrl().isHoldHero()) {
        hold = true;
    }
    return hold;
}

bool t_Custom_Captuer_IsCaptuerHero() {
    return t_custom().captureCtrl().isCapture();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Bound(float,float,int)", Bound, t_SetNextState_Bound);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Jump(float,float,int)", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void JumpCenter(float,int)", JumpCenter, t_SetNextState_JumpCenter);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoStart()", TornadoStart, t_SetNextState_TornadoStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoRise()", TornadoRise, t_SetNextState_TornadoRise);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoFall()", TornadoFall, t_SetNextState_TornadoFall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoSearch(int,float)", TornadoSearch,
                         t_SetNextState_TornadoSearch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoSearchWithCharge(int,int,float)", TornadoSearchWithCharge,
                         t_SetNextState_TornadoSearchWithCharge);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TornadoChase(int)", TornadoChase,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_TornadoChase));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Summon(int,int)", Summon, t_SetNextState_Summon);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void SummonBig(int,int)", SummonBig, t_SetNextState_SummonBig);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void SummonGigant(int,int)", SummonGigant, t_SetNextState_SummonGigant);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Punch()", Punch, t_SetNextState_Punch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void TriplePunch()", TriplePunch, t_SetNextState_TriplePunch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Catch(int,int)", Catch, t_SetNextState_Catch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void EtherJumpStart(int)", EtherJumpStart,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_EtherJumpStart));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void EtherJumpRestart(int)", EtherJumpRestart,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_EtherJumpRestart));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void EtherJumpLanding()", EtherJumpLanding,
                         t_SetNextState_EtherJumpLanding);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void Juggling()", Juggling, t_SetNextState_Juggling);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void JugglingAttack()", JugglingAttack, t_SetNextState_JugglingAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void JugglingAttackFast()", JugglingAttackFast,
                         t_SetNextState_JugglingAttackFast);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void JugglingAttackSearch()", JugglingAttackSearch,
                         t_SetNextState_JugglingAttackSearch);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.SetNextState", "void JugglingAttack2()", JugglingAttack2,
                         t_SetNextState_JugglingAttack2);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "void PunchR_Start(float,int)", PunchR_Start, t_Custom_PunchR_Start);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "void PunchL_Start(float,int)", PunchL_Start, t_Custom_PunchL_Start);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "void Juggling_AddReqData(int)", Juggling_AddReqData,
                         reinterpret_cast<void (*)(u32)>(t_Custom_Juggling_AddReqData));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "void Juggling_ClearReqData()", Juggling_ClearReqData,
                         t_Custom_Juggling_ClearReqData);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "bool Juggling_IsActive()", Juggling_IsActive, t_Custom_Juggling_IsActive);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "bool Juggling_IsHold()", Juggling_IsHold, t_Custom_Juggling_IsHold);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Doubter.Custom", "bool Captuer_IsCaptuerHero()", Captuer_IsCaptuerHero,
                         t_Custom_Captuer_IsCaptuerHero);
}

}

}
}
}
}
