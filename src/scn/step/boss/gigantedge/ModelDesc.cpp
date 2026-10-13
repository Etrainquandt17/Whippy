#include "scn/step/boss/gigantedge/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace gigantedge {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "SwordL",
    "TransL",
    "LShieldJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Appear", 0 },
    { "PreAppear", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
    { "Attack2Start", 0 },
    { "Attack2", 0 },
    { "Attack2End", 0 },
    { "Move", 0 },
    { "MoveBack", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "BreakawayStart", 0 },
    { "Breakaway", 0 },
    { "BreakawayEnd", 0 },
    { "DamageEtc", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
    { "Guard", 0 },
    { "ShieldWait", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "GigantEdge.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.DashEnd.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Attack1.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Attack2.Exec(int)", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Attack2.Exec(int)", 1, 0, 0, 0 },
    { "GigantEdge.AnimScript.Attack2.Exec(int)", 2, 0, 0, 0 },
    { "GigantEdge.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.MoveBack.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Guard.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.Shot.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.JumpAttackStart.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.JumpAttack.Exec", 0, 0, 0, 0 },
    { "GigantEdge.AnimScript.JumpAttackLanding.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<2, 0, 0>(isExtra ? "step/chara/enemy/gigantedge/ModelEx" : "step/chara/enemy/gigantedge/Model",
        "step/chara/enemy/gigantedge/Motion", "GigantEdge", 4, T_NODE_NAMES, 25, T_ANIM_ENTRIES, 19,
        T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::gigantedge
