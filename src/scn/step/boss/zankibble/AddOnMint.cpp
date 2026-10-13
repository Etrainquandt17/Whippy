#include "scn/step/boss/zankibble/AddOnMint.h"

#include "gobj/Target.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mintglue/VectorInline.h"
#include "mintglue/WrapNative.h"
#include "scn/step/Component.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/common/StateDash.h"
#include "scn/step/boss/common/StateJump.h"
#include "scn/step/boss/common/StateMoveForward.h"
#include "scn/step/boss/common/StateMoveJoint.h"
#include "scn/step/boss/zankibble/Param.h"
#include "scn/step/boss/zankibble/ScriptKind.h"
#include "scn/step/boss/zankibble/StateAttack.h"
#include "scn/step/boss/zankibble/StateJumpAttack.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/chara/Location.h"
#include "scn/step/ocoll/AttackType.h"

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

namespace {

void t_SetNextState_MoveStart() {
    common::StateMoveJointDesc desc(MintBoss::Obj().param().zankibble()._24);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveJoint, Boss*, common::StateMoveJointDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_5
    );
}

void t_SetNextState_MoveStartCenter() {
    Boss& owner = MintBoss::Obj();
    Boss& obj = MintBoss::Obj();
    f32 centerX = owner.comp().mainCamera().getCenter().x;
    if (obj.location().pos().x - centerX > 0.0f) {
        MintBoss::Obj().target().setIsRightDir(false);
    } else {
        MintBoss::Obj().target().setIsRightDir(true);
    }
    t_SetNextState_MoveStart();
}

void t_SetNextState_MoveForward() {
    common::StateMoveDesc desc(MintBoss::Obj().param().zankibble()._48);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveForward, Boss*, common::StateMoveDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_6
    );
}

void t_SetNextState_MoveEnd() {
    common::StateMoveJointDesc desc(MintBoss::Obj().param().zankibble()._24);
    MintBoss::Obj().stateChanger().setNextState<common::StateMoveJoint, Boss*, common::StateMoveJointDesc, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_7
    );
}

void t_SetNextState_Dash(bool arg) {
    common::StateDashDesc desc(
        MintBoss::Obj().param().zankibble()._54,
        arg ? MintBoss::Obj().param().zankibble().get64() : MintBoss::Obj().param().zankibble().get58(),
        MintBoss::Obj().param().zankibble()._24,
        MintBoss::Obj().param().zankibble()._28,
        MintBoss::Obj().param().zankibble()._2C,
        MintBoss::Obj().param().zankibble()._70,
        MintBoss::Obj().param().zankibble()._78,
        MintBoss::Obj().param().zankibble()._80,
        true,
        MintBoss::Obj().param().zankibble()._38,
        MintBoss::Obj().param().zankibble()._40,
        GUARD_TYPE_0,
        false,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateDash, Boss*, common::StateDashDesc, ScriptKind, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, arg ? SCRIPT_KIND_9 : SCRIPT_KIND_8, SCRIPT_KIND_10, SCRIPT_KIND_11);
}

void t_SetNextState_AttackStraight(f32 x) {
    StateAttack::Config config;
    config._0 = SCRIPT_KIND_12;
    config._4 = hel::math::Vector2(x, 0.0f);
    config._C = false;
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<StateAttack, Boss*, StateAttack::Config>(&obj, config);
}

void t_SetNextState_AttackCircle(f32 x, f32 y, bool arg) {
    StateAttack::Config config;
    config._0 = arg ? SCRIPT_KIND_15 : SCRIPT_KIND_14;
    config._4 = hel::math::Vector2(x, y);
    config._C = arg;
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<StateAttack, Boss*, StateAttack::Config>(&obj, config);
}

void t_SetNextState_AttackBackCircle(f32 x, f32 y) {
    StateAttack::Config config;
    config._0 = SCRIPT_KIND_16;
    config._4 = hel::math::Vector2(x, y);
    config._C = false;
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<StateAttack, Boss*, StateAttack::Config>(&obj, config);
}

void t_SetNextState_JumpAttack(bool arg) {
    StateJumpAttack::Config config;
    config._0 = arg;
    MintBoss::Obj().stateChanger().setNextState<StateJumpAttackStart, Boss*, StateJumpAttack::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_JumpBack() {
    common::StateJumpDesc desc(
        MintBoss::Obj().param().zankibble()._C0,
        MintBoss::Obj().param().zankibble()._24,
        MintBoss::Obj().param().zankibble()._28,
        MintBoss::Obj().param().zankibble()._2C,
        hel::math::Vector2::ZERO,
        hel::math::Vector2::ZERO,
        false,
        static_cast<common::StateJumpDesc::LandingAnimType>(2),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    MintBoss::Obj().stateChanger().setNextState<common::StateJumpStart, Boss*, common::StateJumpDesc, ScriptKind, ScriptKind>(
        &MintBoss::Obj(), desc, SCRIPT_KIND_19, SCRIPT_KIND_20
    );
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void MoveStart()", MoveStart, t_SetNextState_MoveStart);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void MoveStartCenter()", MoveStartCenter, t_SetNextState_MoveStartCenter);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void MoveForward()", MoveForward, t_SetNextState_MoveForward);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void MoveEnd()", MoveEnd, t_SetNextState_MoveEnd);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void Dash(bool)", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void AttackStraight(float)", AttackStraight, t_SetNextState_AttackStraight);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void AttackCircle(float,float,bool)", AttackCircle,
                         t_SetNextState_AttackCircle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void AttackBackCircle(float,float)", AttackBackCircle,
                         t_SetNextState_AttackBackCircle);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void JumpAttack(bool)", JumpAttack, t_SetNextState_JumpAttack);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.Zankibble.SetNextState", "void JumpBack()", JumpBack, t_SetNextState_JumpBack);
}

}

}
}
}
}
