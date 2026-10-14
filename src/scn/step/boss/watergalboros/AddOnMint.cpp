#include "scn/step/boss/watergalboros/AddOnMint.h"

#include "gobj/MoveParam.h"
#include "hel/common/RuntimeTypeInfoImpl.h"
#include "hel/common/RuntimeTypeInfoInline.h"
#include "hel/math/Vector2.h"
#include "mintglue/WrapNative.h"
#include "scn/step/boss/Boss.h"
#include "scn/step/boss/GuardType.h"
#include "scn/step/boss/ICustom.h"
#include "scn/step/boss/MintBoss.h"
#include "scn/step/boss/Param.h"
#include "scn/step/boss/Utility.h"
#include "scn/step/boss/common/StateDash.h"
#include "scn/step/boss/common/StateJump.h"
#include "scn/step/boss/watergalboros/Custom.h"
#include "scn/step/boss/watergalboros/Param.h"
#include "scn/step/boss/watergalboros/ScriptKind.h"
#include "scn/step/boss/watergalboros/StateAttack.h"
#include "scn/step/boss/watergalboros/StateAttackJoint.h"
#include "scn/step/boss/watergalboros/StateCaptureAttack.h"
#include "scn/step/boss/watergalboros/StateQuivery.h"
#include "scn/step/ocoll/AttackType.h"

using hel::common::DynamicCast;
using hel::math::Vector2;

// The original holds this instance in every unit that sees ICustom; the link keeps only its name string.
template const hel::common::RuntimeTypeInfo& hel::common::RuntimeTypeInfoImpl<scn::step::boss::ICustom>();

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

namespace {

Custom* t_custom() {
    return DynamicCast<Custom*, ICustom>(MintBoss::Obj().custom());
}

void t_SetNextState_JumpSmall() {
    const Param& param = MintBoss::Obj().param().watergalboros();
    common::StateJumpDesc desc(
        param._48,
        param._24,
        gobj::MoveParamDecel::Create(0.0f),
        param._2C,
        Vector2::ZERO,
        Vector2::ZERO,
        false,
        static_cast<common::StateJumpDesc::LandingAnimType>(1),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<common::StateJumpStart, Boss*, common::StateJumpDesc, ScriptKind, ScriptKind>(
        &obj, desc, SCRIPT_KIND_5, SCRIPT_KIND_6
    );
}

void t_SetNextState_Jump() {
    const Param& param = MintBoss::Obj().param().watergalboros();
    common::StateJumpDesc desc(
        param._50,
        param._24,
        gobj::MoveParamDecel::Create(0.0f),
        param._2C,
        Vector2::ZERO,
        Vector2::ZERO,
        true,
        static_cast<common::StateJumpDesc::LandingAnimType>(1),
        false,
        static_cast<ocoll::AttackType>(0x1AB)
    );
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<common::StateJumpStart, Boss*, common::StateJumpDesc, ScriptKind, ScriptKind>(
        &obj, desc, SCRIPT_KIND_5, SCRIPT_KIND_6
    );
}

void t_SetNextState_JumpBig() {
    const Param& param = MintBoss::Obj().param().watergalboros();
    common::StateJumpDesc desc(
        param._58,
        param._24,
        gobj::MoveParamDecel::Create(0.0f),
        param._2C,
        param._38,
        param._40,
        true,
        static_cast<common::StateJumpDesc::LandingAnimType>(0),
        true,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    Boss& obj = MintBoss::Obj();
    Boss& owner = MintBoss::Obj();
    owner.stateChanger().setNextState<common::StateJumpStart, Boss*, common::StateJumpDesc, ScriptKind, ScriptKind>(
        &obj, desc, SCRIPT_KIND_7, SCRIPT_KIND_8
    );
}

void t_SetNextState_AttackStart() {
    MintBoss::Obj().stateChanger().setNextState<StateAttackJoint, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_9);
}

void t_SetNextState_AttackWater() {
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_10);
}

void t_SetNextState_AttackWave() {
    MintBoss::Obj().stateChanger().setNextState<StateAttack, Boss*, ScriptKind>(&MintBoss::Obj(), SCRIPT_KIND_11);
}

void t_SetNextState_Quivery(int a, int b) {
    StateQuivery::Config config;
    config._0 = a;
    config._4 = b;
    MintBoss::Obj().stateChanger().setNextState<StateQuivery, Boss*, StateQuivery::Config>(&MintBoss::Obj(), config);
}

void t_SetNextState_Dash() {
    const Param& param = MintBoss::Obj().param().watergalboros();
    gobj::MoveParamAccel accel = Utility::IsVariationExtra(MintBoss::Obj()) ? param.get90() : param.get84();
    common::StateDashDesc desc(
        param._80,
        accel,
        param._24,
        param._28,
        param._2C,
        param._9C,
        param._A4,
        param._AC,
        true,
        param._38,
        param._40,
        GUARD_TYPE_1,
        false,
        static_cast<ocoll::AttackType>(0x1AC)
    );
    MintBoss::Obj().stateChanger().setNextState<
        common::StateDash, Boss*, common::StateDashDesc, ScriptKind, ScriptKind, ScriptKind
    >(&MintBoss::Obj(), desc, SCRIPT_KIND_14, SCRIPT_KIND_15, SCRIPT_KIND_16);
}

void t_SetNextState_Capture() {
    MintBoss::Obj().stateChanger().setNextState<StateCaptureAttack, Boss*>(&MintBoss::Obj());
}

void t_WeaponCtrl_AddReqData(int a, f32 b, f32 c) {
    WeaponCtrl::ReqData data;
    data._0 = a;
    data._4.x = b;
    data._4.y = c;
    t_custom()->weaponCtrl().addReqData(data);
}

void t_WeaponCtrl_ClearReqBuff() {
    t_custom()->weaponCtrl().clearReqBuff();
}

}

namespace AddOnMint {

void RegisterAll(mintvm::VMCore& core) {
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void JumpSmall()", JumpSmall, t_SetNextState_JumpSmall);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void Jump()", Jump, t_SetNextState_Jump);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void JumpBig()", JumpBig, t_SetNextState_JumpBig);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void AttackStart()", AttackStart, t_SetNextState_AttackStart
    );
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void AttackWater()", AttackWater, t_SetNextState_AttackWater
    );
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void AttackWave()", AttackWave, t_SetNextState_AttackWave);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void Quivery(int,int)", Quivery, t_SetNextState_Quivery);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void Dash()", Dash, t_SetNextState_Dash);
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.SetNextState", "void Capture()", Capture, t_SetNextState_Capture);
    MINT_NATIVE_FUNCTION(
        core, "Scn.Step.Boss.WaterGalboros.WeaponCtrl", "void AddReqData(int,float,float)", AddReqData, t_WeaponCtrl_AddReqData
    );
    MINT_NATIVE_FUNCTION(core, "Scn.Step.Boss.WaterGalboros.WeaponCtrl", "void ClearReqBuff()", ClearReqBuff, t_WeaponCtrl_ClearReqBuff);
}

}

}}}}  // namespace scn::step::boss::watergalboros
