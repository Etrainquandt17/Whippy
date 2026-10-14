#define UTIL_STATECHANGER_FACTORY_ARGUMENTS_BY_REFERENCE
#include "scn/step/boss/fattybuffer/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/fattybuffer/Custom.h"
#include "scn/step/boss/fattybuffer/States.h"

using hel::common::DynamicCastToRef;
using hel::math::Vector3;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

Custom& t_custom() {
    return DynamicCastToRef<Custom, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_Turn() {
    MintBoss::Obj().stateChanger().setNextState<StateTurn, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MoveForward(f32 a) {
    MintBoss::Obj().stateChanger().setNextState<StateMoveForward, Boss*, f32>(&MintBoss::Obj(), a);
}

void t_SetNextState_Jump(f32 a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateJumpStart, Boss*, f32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_StickRoofJump() {
    MintBoss::Obj().stateChanger().setNextState<StateStickRoofJumpStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_StickRoofFall() {
    MintBoss::Obj().stateChanger().setNextState<StateStickRoofFall, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Stamp(bool arg) {
    MintBoss::Obj().stateChanger().setNextState<StateStampStart, Boss*, bool>(&MintBoss::Obj(), arg);
}

void t_SetNextState_Cannon() {
    MintBoss::Obj().stateChanger().setNextState<StateCannon, Boss*, bool>(&MintBoss::Obj(), false);
}

void t_SetNextState_CannonUpper() {
    MintBoss::Obj().stateChanger().setNextState<StateCannon, Boss*, bool>(&MintBoss::Obj(), true);
}

void t_SetNextState_SwellStart() {
    MintBoss::Obj().stateChanger().setNextState<StateSwellStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SwellEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateSwellEnd, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SwellBackJump(f32 a, f32 b) {
    MintBoss::Obj().stateChanger().setNextState<StateSwellBackJumpStart, Boss*, f32, f32>(&MintBoss::Obj(), a, b);
}

void t_SetNextState_SwellRollingAttack(int count) {
    MintBoss::Obj().stateChanger().setNextState<StateSwellRollingAttack, Boss*, unsigned long>(&MintBoss::Obj(), count);
}

void t_SetNextState_SwellRollingAttackCircuit() {
    MintBoss::Obj().stateChanger().setNextState<StateSwellRollingAttackCircuit, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_SwellBalloon(f32 x, f32 y, int count) {
    MintBoss::Obj().stateChanger().setNextState<StateSwellBalloonStart, Boss*, Vector3, unsigned long>(
        &MintBoss::Obj(), Vector3(x, y, 0.0f), count
    );
}

void t_SetNextState_Stalactite(StalactiteJumpKind kind) {
    MintBoss::Obj().stateChanger().setNextState<StateStalactiteStart, Boss*, StalactiteJumpKind>(&MintBoss::Obj(), kind);
}

void t_SetNextState_Disgorge() {
    MintBoss::Obj().stateChanger().setNextState<StateDisgorge, Boss*>(&MintBoss::Obj());
}

void t_EnemyReqBuff_Add(int kind, f32 a, f32 b) {
    EnemyReqBuff::ReqData data;
    data._0 = kind;
    data._4.x = a;
    data._4.y = b;
    t_custom().enemyReqBuff().add(data);
}

void t_EnemyReqBuff_Clear() {
    t_custom().enemyReqBuff().clear();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Turn()", Turn, t_SetNextState_Turn);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void MoveForward(float)", MoveForward, t_SetNextState_MoveForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Jump(float,float)", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void StickRoofJump()", StickRoofJump, t_SetNextState_StickRoofJump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void StickRoofFall()", StickRoofFall, t_SetNextState_StickRoofFall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Stamp(bool)", Stamp, t_SetNextState_Stamp);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Cannon()", Cannon, t_SetNextState_Cannon);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void CannonUpper()", CannonUpper, t_SetNextState_CannonUpper);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellStart()", SwellStart, t_SetNextState_SwellStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellEnd()", SwellEnd, t_SetNextState_SwellEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellBackJump(float,float)", SwellBackJump,
                         t_SetNextState_SwellBackJump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellRollingAttack(int)", SwellRollingAttack,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_SwellRollingAttack));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellRollingAttackCircuit()", SwellRollingAttackCircuit,
                         t_SetNextState_SwellRollingAttackCircuit);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void SwellBalloon(float,float,int)", SwellBalloon,
                         t_SetNextState_SwellBalloon);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Stalactite(int)", Stalactite,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_Stalactite));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.SetNextState", "void Disgorge()", Disgorge, t_SetNextState_Disgorge);

    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.EnemyReqBuff", "void Add(int,float,float)", Add, t_EnemyReqBuff_Add);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.FattyBuffer.EnemyReqBuff", "void Clear()", Clear, t_EnemyReqBuff_Clear);
}

}

}}}}  // namespace scn::step::boss::fattybuffer
