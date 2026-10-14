#include "scn/step/boss/kingsdoo/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateAttack.h"
#include "scn/step/boss/common/StateDash.h"
#include "scn/step/boss/common/StateJump.h"
#include "scn/step/boss/common/StateJumpAttackStart.h"
#include "scn/step/boss/common/StateMoveForward.h"
#include "scn/step/boss/kingsdoo/Param.h"
#include "scn/step/boss/kingsdoo/ScriptKind.h"
#include "scn/step/boss/kingsdoo/StateChargeAttack.h"
#include "scn/step/boss/kingsdoo/StateJumpCenterAttack.h"
#include "scn/step/boss/kingsdoo/StateJumpMachinegun.h"
#include "scn/step/ocoll/AttackType.h"

using hel::math::Vector2;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

namespace {

// TODO: a stand-in, as in gigantedge: the original gets the boss through something inline here.
inline Boss* t_Boss(Boss& boss) {
    return &boss;
}

void t_SetNextState_Attack() {
    common::StateAttackDesc desc(
        MintBoss::Obj().param().kingsdoo()._24,
        Vector2::ZERO,
        Vector2::ZERO,
        0.0f,
        0.0f
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateAttack, Boss*, common::StateAttackDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_8
    );
}

void t_SetNextState_MoveForward() {
    common::StateMoveDesc desc(MintBoss::Obj().param().kingsdoo()._48);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveForward, Boss*, common::StateMoveDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_9
    );
}

void t_SetNextState_Dash() {
    common::StateDashDesc desc(
        MintBoss::Obj().param().kingsdoo()._88,
        MintBoss::Obj().param().kingsdoo()._8C,
        MintBoss::Obj().param().kingsdoo()._24,
        MintBoss::Obj().param().kingsdoo()._28,
        MintBoss::Obj().param().kingsdoo()._2C,
        MintBoss::Obj().param().kingsdoo()._98,
        MintBoss::Obj().param().kingsdoo()._A0,
        MintBoss::Obj().param().kingsdoo()._A8,
        true,
        MintBoss::Obj().param().kingsdoo()._38,
        MintBoss::Obj().param().kingsdoo()._40,
        GUARD_TYPE_0,
        false,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateDash, Boss*, common::StateDashDesc, ScriptKind, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_5, SCRIPT_KIND_6, SCRIPT_KIND_7);
}

void t_SetNextState_JumpBack() {
    common::StateJumpDesc desc(
        t_Boss(MintBoss::Obj())->param().kingsdoo()._54,
        MintBoss::Obj().param().kingsdoo()._24,
        MintBoss::Obj().param().kingsdoo()._28,
        MintBoss::Obj().param().kingsdoo()._2C,
        Vector2::ZERO,
        Vector2::ZERO,
        false,
        static_cast<common::StateJumpDesc::LandingAnimType>(1),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateJumpStart, Boss*, common::StateJumpDesc, ScriptKind, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_10, SCRIPT_KIND_11
    );
}

void t_SetNextState_JumpAttack() {
    common::StateJumpAttackDesc desc(
        MintBoss::Obj().param().kingsdoo()._5C,
        MintBoss::Obj().param().kingsdoo()._28,
        MintBoss::Obj().param().kingsdoo()._2C,
        2
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateJumpAttackStart, Boss*, common::StateJumpAttackDesc, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_12, SCRIPT_KIND_13);
}

void t_SetNextState_JumpCenterAttack() {
    MintBoss::Obj().stateChanger().setNextState<StateJumpCenterAttack, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_JumpMachinegun() {
    MintBoss::Obj().stateChanger().setNextState<StateJumpMachinegunStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ChargeAttackStart() {
    MintBoss::Obj().stateChanger().setNextState<StateChargeAttackStart, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_ChargeAttack(bool arg) {
    StateChargeAttack::Config config;
    config._0 = arg;
    config._1 = false;
    MintBoss::Obj().stateChanger().setNextState<StateChargeAttack, Boss*, StateChargeAttack::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_ChargeAttackPursuit() {
    StateChargeAttack::Config config;
    config._0 = false;
    config._1 = true;
    MintBoss::Obj().stateChanger().setNextState<StateChargeAttack, Boss*, StateChargeAttack::Config>(&MintBoss::Obj(), config);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void Attack()", Attack, t_SetNextState_Attack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void MoveForward()", MoveForward, t_SetNextState_MoveForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void Dash()", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void JumpBack()", JumpBack, t_SetNextState_JumpBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void JumpAttack()", JumpAttack, t_SetNextState_JumpAttack);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.KingsDoo.SetNextState", "void JumpCenterAttack()", JumpCenterAttack, t_SetNextState_JumpCenterAttack
    );
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.KingsDoo.SetNextState", "void JumpMachinegun()", JumpMachinegun, t_SetNextState_JumpMachinegun
    );
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.KingsDoo.SetNextState", "void ChargeAttackStart()", ChargeAttackStart, t_SetNextState_ChargeAttackStart
    );
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.KingsDoo.SetNextState", "void ChargeAttack(bool)", ChargeAttack, t_SetNextState_ChargeAttack);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.KingsDoo.SetNextState", "void ChargeAttackPursuit()", ChargeAttackPursuit,
        t_SetNextState_ChargeAttackPursuit
    );
}

}

}}}}  // namespace scn::step::boss::kingsdoo
