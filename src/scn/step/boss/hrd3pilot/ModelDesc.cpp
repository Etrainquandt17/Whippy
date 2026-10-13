#include "scn/step/boss/hrd3pilot/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3pilot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA3BodyJ",
    "HaveL",
    "CB4BaniaJ",
    "RA2ShoulderJ",
    "Rot2L",
    "CA4TailJ",
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
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "HRD3Pilot.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "HRD3Pilot.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "HRD3Pilot.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "HRD3Pilot.AnimScript.MissileFar.Exec", 0, 0, 0, 0 },
    { "HRD3Pilot.AnimScript.Missile.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<21, 0, 0>(isExtra ? "step/chara/enemy/metalgeneral/ModelEx" : "step/chara/enemy/metalgeneral/ModelEx",
        "step/chara/enemy/metalgeneral/Motion", "HRD3Pilot", 7, T_NODE_NAMES, 41,
        T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::hrd3pilot
