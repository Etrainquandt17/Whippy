#include "scn/step/boss/galactaknight/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace galactaknight {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Control2L",
    "CA3BodyJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Walk", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "JumpEnd", 0 },
    { "Landing", 0 },
    { "Run", 0 },
    { "RunStop", 0 },
    { "GlideStart", 0 },
    { "Glide", 0 },
    { "Flight", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Faint", 0 },
    { "WakeUp", 0 },
    { "ItemGet", 0 },
    { "GuardStart", 0 },
    { "Guard", 0 },
    { "GuardEnd", 0 },
    { "Attack1Start", 0 },
    { "Attack1", 0 },
    { "Attack1End", 0 },
    { "Attack2", 0 },
    { "Attack2End", 0 },
    { "Attack3", 0 },
    { "Attack3End", 0 },
    { "AttackAir", 0 },
    { "AttackHiStart", 0 },
    { "AttackHi", 0 },
    { "AttackHiEnd", 0 },
    { "AttackSideStart", 0 },
    { "AttackSide", 0 },
    { "AttackSideEnd", 0 },
    { "ChoppingStart", 0 },
    { "Chopping", 0 },
    { "FinelyCut", 0 },
    { "FinelyCutEnd", 0 },
    { "UnderThrustStart", 0 },
    { "UnderThrust", 0 },
    { "UnderThrustEnd", 0 },
    { "UnderThrustHit", 0 },
    { "UnderThrustLanding", 0 },
    { "TornadoAttackCharge", 0 },
    { "TornadoAttackChargeMax", 0 },
    { "TornadoAttack", 0 },
    { "WingCondorDiveStart", 0 },
    { "WingCondorDive", 0 },
    { "WingCondorDiveEnd", 0 },
    { "WingShuttleLoop", 0 },
    { "WingShuttleLoopEnd", 0 },
    { "SodoryAttack", 0 },
    { "SodoryAttackAir", 0 },
    { "InCrystal", 0 },
    { "UnRock", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "GalactaKnight.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "GalactaKnight.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.BackStep.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.FrontStep.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.JumpEnd.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.FlyZ.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Guard.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.GuardEnd.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Attack1.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Attack2.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Attack3.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.AttackMince.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.AttackFinish.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.AttackHi.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.AirSpin.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.AirSpin.ExecFall", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.BlastShot.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Thrust.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.ThrustEnd.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.SpinAttackCharge.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.SpinAttack.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.UnderThrust.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.UnderThrustLanding.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.GiantTornadoCharge.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.GiantTornado.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.ThunderSpine.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.RevolutionSword.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.SwordBeamAttack.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.SwordBeamRain.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.TornadoAttackRise.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.TornadoAttack.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.TornadoAttackLanding.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.ShuttleLoop.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.GlideSword.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Init.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.DeadFall.Exec", 0, 0, 0, 0 },
    { "GalactaKnight.AnimScript.DeadEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<20, 0, 0>(
        "step/chara/enemy/Galactic", "step/chara/enemy/Galactic", "GalactaKnight", 3, T_NODE_NAMES, 55, T_ANIM_ENTRIES, 45,
        T_SCRIPT_ENTRIES
    );
    desc._c = hel::math::Vector3(0.0f, 0.5f, 0.0f);
    return desc;
}

}

}
}
}
}
