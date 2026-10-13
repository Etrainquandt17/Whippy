#include "scn/step/boss/metalgeneral/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace metalgeneral {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA3BodyJ",
    "HaveL",
    "CB4BaniaJ",
    "RA2ShoulderJ",
    "Rot2L",
    "Control2L",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Wait2", 0 },
    { "Appear", 0 },
    { "Walk", 0 },
    { "WalkBack", 0 },
    { "Run", 0 },
    { "Back", 0 },
    { "Jump", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "Menace", 0 },
    { "Death", 0 },
    { "SwordAttackStart", 0 },
    { "SwordAttack", 0 },
    { "SwordAttackEnd", 0 },
    { "FinelyCut", 0 },
    { "FinelyCutEnd", 0 },
    { "TurnAttackStart", 0 },
    { "TurnAttack", 0 },
    { "TurnAttackEnd", 0 },
    { "SparkStart", 0 },
    { "SparkCharge", 0 },
    { "Spark", 0 },
    { "ShotStart", 0 },
    { "ShotWait", 0 },
    { "Shot", 0 },
    { "ShotEnd", 0 },
    { "FlightStart", 0 },
    { "Flight", 0 },
    { "FlightEnd", 0 },
    { "BitShotStart", 0 },
    { "BitShot", 0 },
    { "BitShotEnd", 0 },
    { "ShotHiStart", 0 },
    { "ShotHiWait", 0 },
    { "ShotHi", 0 },
    { "ShotHiEnd", 0 },
    { "Patriot", 0 },
    { "PatriotRide", 0 },
    { "RideWait", 0 },
    { "PatriotRideEX", 0 },
    { "RideWaitEX", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MetalGeneral.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.AppearStart.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.WalkForward.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.WalkBack.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Run.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BackStep.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.ZJump.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BeamSwordOnce.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BeamSwordMultiple.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BeamSwordDash.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BeamSwordDashEnd.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Needle.Exec(int)", 1, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Needle.Exec(int)", 2, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Needle.Exec(int)", 3, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Rain.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Missile.Exec(int)", 1, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Missile.Exec(int)", 3, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Missile.Exec(int)", 5, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Missile.Exec(int)", 8, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Circling.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.CirclingFlight.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.CirclingFlightEnd.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Bit.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BombStart.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.Bomb.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.BombEnd.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.PatriotGenerate.Exec(int)", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.PatriotGenerate.Exec(int)", 1, 0, 0, 0 },
    { "MetalGeneral.AnimScript.PatriotClimb.Exec", 0, 0, 0, 0 },
    { "MetalGeneral.AnimScript.PatriotRide.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<11, 0, 0>(isExtra ? "step/chara/enemy/metalgeneral/ModelEx" : "step/chara/enemy/metalgeneral/Model",
        "step/chara/enemy/metalgeneral/Motion", "MetalGeneral", 7, T_NODE_NAMES, 43, T_ANIM_ENTRIES, 38,
        T_SCRIPT_ENTRIES);
}

}

}
}
}
}
