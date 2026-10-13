#include "scn/step/boss/moundeath/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace moundeath {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TransL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "BigJumpPressLanding", 0 },
    { "Landing", 0 },
    { "Fall", 0 },
    { "DeathDamage", 0 },
    { "DeathStart", 0 },
    { "Death", 0 },
    { "MoveStart", 0 },
    { "Move", 0 },
    { "MoveEnd", 0 },
    { "JumpStart", 0 },
    { "JumpStart", 0 },
    { "BigJumpPressLanding", 0 },
    { "RunAttack", 0 },
    { "DamageEtc", 0 },
    { "Landing", 0 },
    { "Wait", 0 },
    { "Landing", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Moundeath.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.MoveStart.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.MoveEnd.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressJumpStart.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressJump.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressJumpLanding.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressFallStart.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressBigJump.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.PressBigJumpLanding.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.GiantJumpLanding.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.GiantFallStart.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.GiantFall.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.RollJumpStart.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.RollJump.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.RollJumpLanding.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.DashWallHit.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.DashEnd.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.Rolling.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.RollingEnd.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.TornadoRise.Exec", 0, 0, 0, 0 },
    { "Moundeath.AnimScript.TornadoChase.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<10, 0, 0>(isExtra ? "step/chara/enemy/moundeath/ModelEx" : "step/chara/enemy/moundeath/Model",
        "step/chara/enemy/moundeath/Motion", "Moundeath", 2, T_NODE_NAMES, 18, T_ANIM_ENTRIES, 28,
        T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::moundeath
