#include "scn/step/boss/mahoroaroah/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace mahoroaroah {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PtclR1L",
    "PtclR2L",
    "PtclR3L",
    "PtclL1L",
    "PtclL2L",
    "PtclL3L",
    "PtclCL",
    "BodyM",
    "MantAllJ",
    "CA2BodyCoreJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "ShipWait", 0 },
    { "Loop", 0 },
    { "ShipAppear", 0 },
    { "ShipOarAttackStart", 0 },
    { "ShipOarAttackWait", 0 },
    { "ShipOarAttackShot", 0 },
    { "ShipOarAttack", 0 },
    { "ShipOarAttackEnd", 0 },
    { "ShipWarpIn", 0 },
    { "ShipWarpOut", 0 },
    { "ShipWingAttack", 0 },
    { "ShipMastAttackStart", 0 },
    { "ShipMastAttack", 0 },
    { "ShipMastAttackEnd", 0 },
    { "ShipEnergyShotStart", 0 },
    { "ShipEnergyShotWait", 0 },
    { "ShipEnergyShot", 0 },
    { "ShipEnergyShotAttackWait", 0 },
    { "ShipEnergyShotEnd", 0 },
    { "ShipAttack", 0 },
    { "ShipMenace", 0 },
    { "Wait", 0 },
    { "WarpIn", 0 },
    { "WarpOut", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MahoroaRoah.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.AppearWarpIn.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Star.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Boomerang.Exec(int)", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Boomerang.Exec(int)", 1, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Boomerang.Exec(int)", 2, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Storm.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.StormEnd.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Oar.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.WarpIn.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.WarpOut.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 1, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 2, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 3, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 4, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 5, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Bullet.Exec(int)", 6, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.EscapeWarpIn.Exec", 0, 0, 0, 0 },
    { "MahoroaRoah.AnimScript.EscapeWarpOut.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<17, 0, 0>("step/chara/enemy/mahoroabattle1/Model", "step/chara/enemy/mahoroabattle1/Motion", "MahoroaRoah", 11, T_NODE_NAMES,
        24, T_ANIM_ENTRIES, 25, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 3;
    return desc;
}

}

}
}
}
}
