#include "scn/step/boss/watergalboros/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace watergalboros {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Appear", 0 },
    { "Landing", 0 },
    { "Fall", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
    { "Preparation", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
    { "WaveStart", 0 },
    { "Wave", 0 },
    { "WaveEnd", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "SplashStart", 0 },
    { "Splash", 0 },
    { "SplashEnd", 0 },
    { "WaveStart", 0 },
    { "Attack", 0 },
    { "DamageEtc", 0 },
    { "Landing", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "WaterGalboros.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.JumpBigStart.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.JumpBig.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.AttackPrepare.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.AttackWater.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.AttackWave.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Quivery.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.QuiveryEnd.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.DashEnd.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.CaptureAttack.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Capture.Exec", 0, 0, 0, 0 },
    { "WaterGalboros.AnimScript.Vomit.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<4, 0, 0>(isExtra ? "step/chara/enemy/watergalboros/ModelEx" : "step/chara/enemy/watergalboros/Model",
        "step/chara/enemy/watergalboros/Motion", "WaterGalboros", 1, T_NODE_NAMES, 25, T_ANIM_ENTRIES, 20,
        T_SCRIPT_ENTRIES);
}

}

}
}
}
}
