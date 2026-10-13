#include "scn/step/boss/gigantedge/AddOnMint.h"

#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateAttack.h"
#include "scn/step/boss/common/StateDash.h"
#include "scn/step/boss/common/StateJumpAttackStart.h"
#include "scn/step/boss/common/StateMoveBack.h"
#include "scn/step/boss/common/StateMoveForward.h"
#include "scn/step/boss/gigantedge/Param.h"
#include "scn/step/boss/gigantedge/ScriptKind.h"
#include "scn/step/boss/gigantedge/StateGuard.h"
#include "scn/step/boss/gigantedge/StateShot.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

namespace {

// TODO: a stand-in, like the two locals of the attacks. The original passes the boss through something inline that
// keeps it in a register while the other arguments are made; what that is, is not known.
inline Boss* t_Boss(Boss& boss) {
    return &boss;
}

void t_SetNextState_Attack1() {
    Boss* obj0 = t_Boss(MintBoss::Obj());
    Boss* obj1 = t_Boss(MintBoss::Obj());
    common::StateAttackDesc desc(
        MintBoss::Obj().param().gigantedge()._38,
        MintBoss::Obj().param().gigantedge()._A0,
        MintBoss::Obj().param().gigantedge()._A8,
        obj1->param().gigantedge()._B0,
        obj0->param().gigantedge()._B4
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateAttack, Boss*, common::StateAttackDesc, ScriptKind>(
        t_Boss(MintBoss::Obj()), desc, SCRIPT_KIND_8
    );
}

void t_SetNextState_Attack2(int index) {
    Boss* obj0 = t_Boss(MintBoss::Obj());
    Boss* obj1 = t_Boss(MintBoss::Obj());
    common::StateAttackDesc desc(
        MintBoss::Obj().param().gigantedge()._38,
        MintBoss::Obj().param().gigantedge()._A0,
        MintBoss::Obj().param().gigantedge()._A8,
        obj1->param().gigantedge()._B0,
        obj0->param().gigantedge()._B4
    );
    ScriptKind kind = SCRIPT_KIND_9;
    switch (index) {
    case 0:
        kind = SCRIPT_KIND_9;
        break;
    case 1:
        kind = SCRIPT_KIND_10;
        break;
    case 2:
        kind = SCRIPT_KIND_11;
        break;
    }
    MintBoss::Obj().stateChanger().setNextState<common::StateAttack, Boss*, common::StateAttackDesc, ScriptKind>(
        t_Boss(MintBoss::Obj()), desc, kind
    );
}

void t_SetNextState_MoveForward() {
    common::StateMoveDesc desc(MintBoss::Obj().param().gigantedge()._5C);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveForward, Boss*, common::StateMoveDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_12
    );
}

void t_SetNextState_MoveBack() {
    common::StateMoveDesc desc(MintBoss::Obj().param().gigantedge()._68);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveBack, Boss*, common::StateMoveDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_13
    );
}

void t_SetNextState_Dash(bool arg) {
    common::StateDashDesc desc(
        MintBoss::Obj().param().gigantedge()._74,
        MintBoss::Obj().param().gigantedge()._78,
        MintBoss::Obj().param().gigantedge()._9C,
        MintBoss::Obj().param().gigantedge()._3C,
        MintBoss::Obj().param().gigantedge()._40,
        MintBoss::Obj().param().gigantedge()._84,
        MintBoss::Obj().param().gigantedge()._8C,
        MintBoss::Obj().param().gigantedge()._94,
        true,
        MintBoss::Obj().param().gigantedge()._4C,
        MintBoss::Obj().param().gigantedge()._54,
        GUARD_TYPE_0,
        arg,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateDash, Boss*, common::StateDashDesc, ScriptKind, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_5, SCRIPT_KIND_6, SCRIPT_KIND_7);
}

void t_SetNextState_Guard() {
    MintBoss::Obj().stateChanger().setNextState<StateGuard, Boss*>(&MintBoss::Obj());
}

void t_SetNextState_Shot(bool arg) {
    StateShot::Config config = {arg};
    MintBoss::Obj().stateChanger().setNextState<StateShot, Boss*, StateShot::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_JumpAttack() {
    common::StateJumpAttackDesc desc(
        MintBoss::Obj().param().gigantedge()._C8,
        MintBoss::Obj().param().gigantedge()._3C,
        MintBoss::Obj().param().gigantedge()._D0,
        18
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateJumpAttackStart, Boss*, common::StateJumpAttackDesc, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_16, SCRIPT_KIND_17);
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void Attack1()", Attack1, t_SetNextState_Attack1);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void Attack2(int)", Attack2, t_SetNextState_Attack2);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.GigantEdge.SetNextState", "void MoveForward()", MoveForward, t_SetNextState_MoveForward
    );
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void MoveBack()", MoveBack, t_SetNextState_MoveBack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void Dash(bool)", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void Guard()", Guard, t_SetNextState_Guard);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.GigantEdge.SetNextState", "void Shot(bool)", Shot, t_SetNextState_Shot);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.GigantEdge.SetNextState", "void JumpAttack()", JumpAttack, t_SetNextState_JumpAttack
    );
}

}

}
}
}
}
