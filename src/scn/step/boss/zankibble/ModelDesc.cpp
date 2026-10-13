#include "scn/step/boss/zankibble/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace zankibble {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RCutterL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Appear", 0 },
    { "PreAppear", 0 },
    { "Landing", 0 },
    { "Fall", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
    { "MoveStart", 0 },
    { "Move", 0 },
    { "MoveEnd", 0 },
    { "DashCutterStart", 0 },
    { "DashCutter", 0 },
    { "DashCutterEnd", 0 },
    { "DashCutterEnd", 0 },
    { "CutterEllipseThrow", 0 },
    { "CutterCatch", 0 },
    { "CutterThrow", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "JumpingCutterThrow", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Zankibble.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Landing.Exec(int)", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.MoveStart.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.MoveEnd.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Dash.Exec(int)", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Dash.Exec(int)", 1, 0, 0, 0 },
    { "Zankibble.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.DashEnd.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.AttackStraight.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Catch.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.AttackCircle.Exec(int)", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.AttackCircle.Exec(int)", 1, 0, 0, 0 },
    { "Zankibble.AnimScript.AttackCircle.Exec(int)", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.JumpAttackStart.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.JumpAttack.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "Zankibble.AnimScript.Landing.Exec(int)", 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<6, 0, 0>(isExtra ? "step/chara/enemy/zankibble/ModelEx" : "step/chara/enemy/zankibble/Model",
        "step/chara/enemy/zankibble/Motion", "Zankibble", 2, T_NODE_NAMES, 21, T_ANIM_ENTRIES, 22,
        T_SCRIPT_ENTRIES);
}

}

}
}
}
}
