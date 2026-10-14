#include "scn/step/boss/moundeath/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateDash.h"
#include "scn/step/boss/common/StateJump.h"
#include "scn/step/boss/common/StateLanding.h"
#include "scn/step/boss/common/StateMoveJoint.h"
#include "scn/step/boss/moundeath/Param.h"
#include "scn/step/boss/moundeath/ScriptKind.h"
#include "scn/step/boss/moundeath/States.h"
#include "scn/step/ocoll/AttackType.h"

using hel::math::Vector2;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

namespace {

void t_SetNextState_MoveStart() {
    common::StateMoveJointDesc desc(MintBoss::Obj().param().moundeath()._24);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveJoint, Boss*, common::StateMoveJointDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_5
    );
}

void t_SetNextState_MoveForward() {
    MintBoss::Obj().stateChanger().setNextState<StateMoveForward, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_MoveEnd() {
    common::StateMoveJointDesc desc(MintBoss::Obj().param().moundeath()._24);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveJoint, Boss*, common::StateMoveJointDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_7
    );
}

void t_SetNextState_Jump() {
    MintBoss::Obj().stateChanger().setNextState<StateJump, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_JumpBack() {
    common::StateJumpDesc desc(
        MintBoss::Obj().param().moundeath()._6C,
        MintBoss::Obj().param().moundeath()._24,
        MintBoss::Obj().param().moundeath()._28,
        MintBoss::Obj().param().moundeath()._38,
        Vector2::ZERO,
        Vector2::ZERO,
        false,
        static_cast<common::StateJumpDesc::LandingAnimType>(1),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateJump, Boss*, common::StateJumpDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_8
    );
}

void t_SetNextState_Press() {
    MintBoss::Obj().stateChanger().setNextState<StatePressJumpStart, Boss*, JumpKind>(&MintBoss::Obj(), JUMP_KIND_0);
}

void t_SetNextState_PressBig() {
    MintBoss::Obj().stateChanger().setNextState<StatePressJumpStart, Boss*, JumpKind>(&MintBoss::Obj(), JUMP_KIND_1);
}

void t_SetNextState_GiantJump() {
    MintBoss::Obj().stateChanger().setNextState<StatePressJumpStart, Boss*, JumpKind>(&MintBoss::Obj(), JUMP_KIND_2);
}

void t_SetNextState_RollJumpStart() {
    MintBoss::Obj().stateChanger().setNextState<StatePressJumpStart, Boss*, JumpKind>(&MintBoss::Obj(), JUMP_KIND_3);
}

void t_SetNextState_RollJumpRestart() {
    StateRollJump::Config config;
    config._0 = false;
    MintBoss::Obj().stateChanger().setNextState<StateRollJump, Boss*, StateRollJump::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_RollJumpLanding() {
    MintBoss::Obj().stateChanger().setNextState<common::StateLanding, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_20);
}

void t_SetNextState_Dash() {
    const Param& param = MintBoss::Obj().param().moundeath();
    common::StateDashDesc desc(
        param._D4,
        param._D8,
        param._24,
        param._28,
        param._38,
        param._E4,
        param._EC,
        param._F4,
        true,
        param._44,
        param._4C,
        static_cast<GuardType>(1),
        false,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateDash, Boss*, common::StateDashDesc, ScriptKind, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_21, SCRIPT_KIND_22, SCRIPT_KIND_23);
}

void t_SetNextState_Rolling() {
    MintBoss::Obj().stateChanger().setNextState<StateRollingStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Tornado() {
    MintBoss::Obj().stateChanger().setNextState<StateTornadoRise, Boss*>(&MintBoss::Obj());
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void MoveStart()", MoveStart, t_SetNextState_MoveStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void MoveForward()", MoveForward, t_SetNextState_MoveForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void MoveEnd()", MoveEnd, t_SetNextState_MoveEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void JumpBack()", JumpBack, t_SetNextState_JumpBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void Press()", Press, t_SetNextState_Press);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void PressBig()", PressBig, t_SetNextState_PressBig);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void GiantJump()", GiantJump, t_SetNextState_GiantJump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void RollJumpStart()", RollJumpStart, t_SetNextState_RollJumpStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void RollJumpRestart()", RollJumpRestart, t_SetNextState_RollJumpRestart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void RollJumpLanding()", RollJumpLanding, t_SetNextState_RollJumpLanding);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void Dash()", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void Rolling()", Rolling, t_SetNextState_Rolling);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Moundeath.SetNextState", "void Tornado()", Tornado, t_SetNextState_Tornado);
}

}

}}}}  // namespace scn::step::boss::moundeath
