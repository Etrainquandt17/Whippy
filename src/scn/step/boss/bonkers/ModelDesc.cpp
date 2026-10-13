#include "scn/step/boss/bonkers/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace bonkers {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "LA6HammertopJ",
    "HammerEffectL",
    "StarL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Appear", 0 },
    { "DownStart", 0 },
    { "DownBound", 0 },
    { "DownWait", 0 },
    { "HammerStart", 0 },
    { "HammerCharge", 0 },
    { "HammerHit", 0 },
    { "Onigoroshi", 0 },
    { "Run", 0 },
    { "Landing", 0 },
    { "Fall", 0 },
    { "SmallJump", 0 },
    { "SmallJumpEnd", 0 },
    { "SmallJumpFall", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "JumpEnd", 0 },
    { "HammerDashStart", 0 },
    { "HammerDash", 0 },
    { "HammerDashEnd", 0 },
    { "BombThroughStart", 0 },
    { "BombThrowCharge", 0 },
    { "BombThroughLoop", 0 },
    { "BombThroughEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Bonkers.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Hammer.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.FireHammer.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.StampFoot.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.JumpBigStart.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.JumpBig.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.Swing.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.SwingEnd.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.BombStart.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.BombLoop.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.BombLast.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.RainBombStart.Exec", 0, 0, 0, 0 },
    { "Bonkers.AnimScript.RainBomb.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& CreateNormal(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<7, 0, 0>(isExtra ? "step/chara/enemy/bonkers/ModelEx" : "step/chara/enemy/bonkers/Model",
                                                "step/chara/enemy/bonkers/Motion", "Bonkers", 4, T_NODE_NAMES, 25, T_ANIM_ENTRIES, 18,
                                                T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateSuper(u32 level, bool isExtra) {
    return boss::ModelDesc::CreateTmpl<7, 0, 1>(isExtra ? "step/chara/enemy/bonkers/ModelSpEx" : "step/chara/enemy/bonkers/ModelSp",
                                                "step/chara/enemy/bonkers/Motion", "Bonkers", 4, T_NODE_NAMES, 25, T_ANIM_ENTRIES, 18,
                                                T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::boss::bonkers
