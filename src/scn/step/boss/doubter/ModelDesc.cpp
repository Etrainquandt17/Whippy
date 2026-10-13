#include "scn/step/boss/doubter/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace doubter {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HandMasterJ",
    "RHandTransJ",
    "LHandTransJ",
    "RHandJ",
    "LHandJ",
    "RFinger2AJ",
    "LFinger2AJ",
    "CA4TrunkJ",
    "CA5NeckJ",
    "CA6HeadJ",
    "HatL",
    "Ball1L",
    "Ball2L",
    "Ball3L",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Appear", 0 },
    { "AppearStart", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "PunchStart", 0 },
    { "Punch", 0 },
    { "PunchWait", 0 },
    { "PunchEnd", 0 },
    { "ReamPunchStart", 0 },
    { "1ReamPunch", 0 },
    { "2ReamPunch", 0 },
    { "3ReamPunch", 0 },
    { "ReamPunchWait", 0 },
    { "ReamPunchEnd", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
    { "JugglingStart", 0 },
    { "Juggling", 0 },
    { "JugglingNoBallEnd", 0 },
    { "JugglingFall", 0 },
    { "JugglingLanding", 0 },
    { "JugglingJump", 0 },
    { "JugglingJumpStart", 0 },
    { "ShotStart", 0 },
    { "ShotWait", 0 },
    { "Preliminary", 0 },
    { "Shot", 0 },
    { "ShotEnd", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Death", 0 },
    { "Transform", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Doubter.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.LandingWithAttack.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.AppearStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.BoundStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Bound.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.TornadoStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.TornadoRise.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.TornadoFall.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.TornadoSearch.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.TornadoChase.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Punch.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.ReamPunch.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.CatchSearch.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Catch.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec0", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec1", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec2", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec3", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec4", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec5", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec6", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Summon.Exec7", 0, 0, 0, 0 },
    { "Doubter.AnimScript.JugglingStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.JugglingAttack1.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.JugglingAttack2.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.EtherJumpStart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.EtherJumpRise.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.EtherJumpFall.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.EtherJumpRestart.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.EtherJumpLanding.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "Doubter.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<3, 0, 0>(isExtra ? "step/chara/enemy/doubter/ModelEx" : "step/chara/enemy/doubter/Model",
        "step/chara/enemy/doubter/Motion", "Doubter", 15, T_NODE_NAMES, 36, T_ANIM_ENTRIES, 39,
        T_SCRIPT_ENTRIES);
}

}

}
}
}
}
