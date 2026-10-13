#include "scn/step/boss/dubior/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace dubior {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Attack1Loop", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
    { "CallStart", 0 },
    { "CallLoop", 0 },
    { "CallEnd", 0 },
    { "Attack1Start", 0 },
    { "Attack1Loop", 0 },
    { "Attack1End", 0 },
    { "Attack1Start", 0 },
    { "Wait1", 0 },
    { "DamageEtc", 0 },
    { "Attack1Start", 0 },
    { "Attack1Start", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Dubior.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "Dubior.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Call.Exec", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Dash.Exec(int)", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Dash.Exec(int)", 1, 0, 0, 0 },
    { "Dubior.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "Dubior.AnimScript.ThunderStart.Exec", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Thunder.Exec(int)", 0, 0, 0, 0 },
    { "Dubior.AnimScript.Thunder.Exec(int)", 1, 0, 0, 0 },
    { "Dubior.AnimScript.Shot.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<8, 0, 0>(isExtra ? "step/chara/enemy/dubior/ModelEx" : "step/chara/enemy/dubior/Model",
        "step/chara/enemy/dubior/Motion", "Dubior", 1, T_NODE_NAMES, 16, T_ANIM_ENTRIES, 13,
        T_SCRIPT_ENTRIES);
}

}

}
}
}
}
