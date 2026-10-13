#include "scn/step/boss/roah/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace roah {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "RotL",
    "Ptcl1L",
    "Ptcl2L",
    "StarMain",
    "WingLL",
    "WingRL",
    "Engines",
    "MastL",
    "BodyCollL",
    "CockpitWindowFront",
    "OarL",
    "LKai1L",
    "LKai2L",
    "LKai3L",
    "RKai1L",
    "RKai2L",
    "RKai3L",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "WingShot", 0 },
    { "Loop", 0 },
    { "OarLoop", 0 },
    { "WingShot", 0 },
    { "WingCatch", 0 },
    { "EmblemAttack", 0 },
    { "OarAttackStart", 0 },
    { "OarAttackEnd", 0 },
    { "MastAttackStart", 0 },
    { "MastAttack", 0 },
    { "MastAttackEnd", 0 },
    { "EnergyShot", 0 },
    { "Death", 0 },
    { "WingCatch", 0 },
    { "Menace", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Roah.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "Roah.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.AppearStart.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Star.Exec(int)", 1, 0, 0, 0 },
    { "Roah.AnimScript.Star.Exec(int)", 3, 0, 0, 0 },
    { "Roah.AnimScript.Star.Exec(int)", 5, 0, 0, 0 },
    { "Roah.AnimScript.Boomerang.Exec(int)", 0, 0, 0, 0 },
    { "Roah.AnimScript.Boomerang.Exec(int)", 1, 0, 0, 0 },
    { "Roah.AnimScript.Boomerang.Exec(int)", 2, 0, 0, 0 },
    { "Roah.AnimScript.BoomerangCatch.Exec(int)", 0, 0, 0, 0 },
    { "Roah.AnimScript.BoomerangCatch.Exec(int)", 1, 0, 0, 0 },
    { "Roah.AnimScript.Storm.Exec(int)", 0, 0, 0, 0 },
    { "Roah.AnimScript.Storm.Exec(int)", 1, 0, 0, 0 },
    { "Roah.AnimScript.StormWait.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.StormEnd.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Oar.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.OarEnd.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Tackle.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Bullet.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "Roah.AnimScript.Anger.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<14, 0, 0>(
        isExtra ? "step/chara/enemy/roah/ModelEx" : "step/chara/enemy/roah/Model", "step/chara/enemy/roah/Motion", "Roah", 19,
        T_NODE_NAMES, 16, T_ANIM_ENTRIES, 25, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 3;
    return desc;
}

}

}
}
}
}
