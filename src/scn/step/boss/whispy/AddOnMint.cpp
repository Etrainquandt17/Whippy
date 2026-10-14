#include "scn/step/boss/whispy/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/whispy/Custom.h"
#include "scn/step/boss/whispy/EnemyReqBuff.h"
#include "scn/step/boss/whispy/ScriptKind.h"
#include "scn/step/boss/whispy/StateFallEnemy.h"
#include "scn/step/boss/whispy/StateRootAttack.h"
#include "scn/step/boss/whispy/StateShotAirBall.h"
#include "scn/step/boss/whispy/StateShotAirBallBig.h"
#include "scn/step/boss/whispy/StateShotAirBallTornado.h"
#include "scn/step/boss/whispy/StateVacuumStart.h"

using hel::common::DynamicCastToRef;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace whispy {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_ShotAirBall(int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateShotAirBall, Boss*, u32, u32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_ShotAirBallBig(int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateShotAirBallBig, Boss*, u32, u32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_ShotAirBallTornado(int a, int b, int c) {
    MintBoss::Obj().stateChanger().setNextState<StateShotAirBallTornado, Boss*, u32, u32, u32>(&MintBoss::Obj(), a, b, c);
}

void t_SetNextState_FallApple(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateFallEnemy, Boss*, ScriptKind, u32>(&MintBoss::Obj(), ScriptKind_FallApple, index);
}

void t_SetNextState_FallEnemy(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateFallEnemy, Boss*, ScriptKind, u32>(&MintBoss::Obj(), ScriptKind_FallEnemy, index);
}

void t_SetNextState_FallEnemy2(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateFallEnemy, Boss*, ScriptKind, u32>(&MintBoss::Obj(), ScriptKind_FallEnemy2, index);
}

void t_SetNextState_Vacuum() {
    MintBoss::Obj().stateChanger().setNextState<StateVacuumStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_RootAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateRootAttack, Boss*>(&MintBoss::Obj());
}

void t_EnemyReqBuff_Add(int a, int b, int c) {
    EnemyReqBuff::ReqData data = {a, b, c};
    t_custom().enemyReqBuff().add(data);
}

void t_FaceRotCtrl_Set(f32 rot) {
    t_custom().faceRotCtrl().setRotate(rot);
}

void t_FaceRotCtrl_Reset() {
    t_custom().faceRotCtrl().reset();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void ShotAirBall(int,int,int)", ShotAirBall, t_SetNextState_ShotAirBall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void ShotAirBallBig(int,int,int)", ShotAirBallBig, t_SetNextState_ShotAirBallBig);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void ShotAirBallTornado(int,int,int)", ShotAirBallTornado,
                         t_SetNextState_ShotAirBallTornado);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void FallApple(int)", FallApple,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_FallApple));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void FallEnemy(int)", FallEnemy,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_FallEnemy));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void FallEnemy2(int)", FallEnemy2,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_FallEnemy2));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void Vacuum()", Vacuum, t_SetNextState_Vacuum);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.SetNextState", "void RootAttack()", RootAttack, t_SetNextState_RootAttack);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.EnemyReqBuff", "void Add(int,int,int)", Add, t_EnemyReqBuff_Add);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.FaceRotCtrl", "void Set(float)", Set, t_FaceRotCtrl_Set);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Whispy.FaceRotCtrl", "void Reset()", Reset, t_FaceRotCtrl_Reset);
}

}

}}}}  // namespace scn::step::boss::whispy
