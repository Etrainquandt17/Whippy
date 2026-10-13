#include "scn/step/boss/kingsdoo/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace kingsdoo {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Beam1J",
    "Beam2J",
    "Beam3J",
    "Beam4J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Appear", 0 },
    { "PreAppear", 0 },
    { "Landing", 0 },
    { "Fall", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "Move", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "Landing", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "BeamAir", 0 },
    { "PreAppear", 0 },
    { "Attack", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "KingsDoo.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.DashEnd.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpAttackStart.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpAttack.Exec(int)", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpAttack.Exec(int)", 1, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpMachinegunStart.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.JumpMachinegun.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.ChargeAttackStart.Exec", 0, 0, 0, 0 },
    { "KingsDoo.AnimScript.ChargeAttack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<5, 0, 0>(isExtra ? "step/chara/enemy/beholdoo/ModelEx" : "step/chara/enemy/beholdoo/Model",
        "step/chara/enemy/beholdoo/Motion", "KingsDoo", 5, T_NODE_NAMES, 19, T_ANIM_ENTRIES, 19,
        T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::kingsdoo
