#include "scn/step/boss/metalgeneral/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/metalgeneral/ScriptKind.h"
#include "scn/step/boss/metalgeneral/States.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

void t_SetNextState_WalkForward() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveGround, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_7);
}

void t_SetNextState_WalkBack() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveGround, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_8);
}

void t_SetNextState_Run() {
    MintBoss::Obj().stateChanger().setNextState<StateRun, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BackStep() {
    MintBoss::Obj().stateChanger().setNextState<StateBackStep, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_BeamSwordOnce() {
    MintBoss::Obj().stateChanger().setNextState<StateBeamSword, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_15);
}

void t_SetNextState_BeamSwordMultiple() {
    MintBoss::Obj().stateChanger().setNextState<StateBeamSword, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_16);
}

void t_SetNextState_BeamSwordDash() {
    MintBoss::Obj().stateChanger().setNextState<StateBeamSwordDash, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_CenterJump() {
    MintBoss::Obj().stateChanger().setNextState<StateCenterJump, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Needle(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateNeedle, Boss*, unsigned long>(&MintBoss::Obj(), index);
}

void t_SetNextState_Rain() {
    MintBoss::Obj().stateChanger().setNextState<StateRain, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Missile(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateMissile, Boss*, unsigned long>(&MintBoss::Obj(), index);
}

void t_SetNextState_Circling() {
    MintBoss::Obj().stateChanger().setNextState<StateCirclingJump, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Bit(int index) {
    MintBoss::Obj().stateChanger().setNextState<StateBit, Boss*, unsigned long>(&MintBoss::Obj(), index);
}

void t_SetNextState_BombStart() {
    MintBoss::Obj().stateChanger().setNextState<StateBombJoint, Boss*, StateBombJoint::JointKind>(
        &MintBoss::Obj(), StateBombJoint::JOINT_KIND_0
    );
}

void t_SetNextState_BombLoop(f32 a, f32 b, bool c) {
    StateBomb::Config config(a, b, c);
    MintBoss::Obj().stateChanger().setNextState<StateBomb, Boss*, StateBomb::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_BombEnd() {
    MintBoss::Obj().stateChanger().setNextState<StateBombJoint, Boss*, StateBombJoint::JointKind>(
        &MintBoss::Obj(), StateBombJoint::JOINT_KIND_1
    );
}

void t_SetNextState_PatriotStatic(unsigned long count) {
    StatePatriotGenerate::Config config;
    config._0 = count;
    config._4 = false;
    config._8 = 0;
    MintBoss::Obj().stateChanger().setNextState<StatePatriotGenerate, Boss*, StatePatriotGenerate::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_PatriotAfterJump(int kind) {
    if (kind == 2) {
        StatePatriotGenerate::Config config;
        config._0 = 1;
        config._4 = false;
        config._8 = kind;
        MintBoss::Obj().stateChanger().setNextState<StatePatriotZJump, Boss*, StatePatriotGenerate::Config>(&MintBoss::Obj(), config);
    } else {
        StatePatriotGenerate::Config config;
        config._0 = 1;
        config._4 = true;
        config._8 = kind;
        bool isFirst = kind == 0;
        MintBoss::Obj().stateChanger().setNextState<StatePatriotJump, Boss*, StatePatriotGenerate::Config, bool>(
            &MintBoss::Obj(), config, isFirst
        );
    }
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void WalkForward()", WalkForward, t_SetNextState_WalkForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void WalkBack()", WalkBack, t_SetNextState_WalkBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Run()", Run, t_SetNextState_Run);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BackStep()", BackStep, t_SetNextState_BackStep);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BeamSwordOnce()", BeamSwordOnce, t_SetNextState_BeamSwordOnce);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BeamSwordMultiple()", BeamSwordMultiple,
                         t_SetNextState_BeamSwordMultiple);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BeamSwordDash()", BeamSwordDash, t_SetNextState_BeamSwordDash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void CenterJump()", CenterJump, t_SetNextState_CenterJump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Needle(int)", Needle,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_Needle));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Rain()", Rain, t_SetNextState_Rain);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Missile(int)", Missile,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_Missile));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Circling()", Circling, t_SetNextState_Circling);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void Bit(int)", Bit, reinterpret_cast<void (*)(u32)>(t_SetNextState_Bit));
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BombStart()", BombStart, t_SetNextState_BombStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BombLoop(float,float,bool)", BombLoop, t_SetNextState_BombLoop);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void BombEnd()", BombEnd, t_SetNextState_BombEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void PatriotStatic(int)", PatriotStatic, t_SetNextState_PatriotStatic);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.MetalGeneral.SetNextState", "void PatriotAfterJump(int)", PatriotAfterJump,
                         reinterpret_cast<void (*)(u32)>(t_SetNextState_PatriotAfterJump));
}

}

}
}
}
}
