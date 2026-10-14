#include "scn/step/enemy/landiasingle/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace landiasingle {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotL",
    "CA4MouthJ",
    "CrownL",
    "CA3HeadJ",
    "EyeLL",
    "EyeRL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "FlightWait", 0 },
    { "Flap", 0 },
    { "Flight", 0 },
    { "GlideStart", 0 },
    { "Glide", 0 },
    { "GlideEnd", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "DeathFall", 0 },
    { "DeathLanding", 0 },
    { "DeathLoop", 0 },
    { "MakeFireBall", 0 },
    { "Formation", 0 },
    { "UpPass", 0 },
    { "FrontPass", 0 },
    { "UnderPass", 0 },
    { "FireRainStart", 0 },
    { "FireRain", 0 },
    { "FireRainEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "LandiaSingle.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.TurnFrontWait.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.Move.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.GlideStart.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.Glide.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.GlideEnd.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassWait.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassMakeFireBall.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassUp.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassFront.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassUnder.Exec(int)", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FormationPassUnder.Exec(int)", 1, 0, 0, 0 },
    { "LandiaSingle.AnimScript.FireRain.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.PreDead.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "LandiaSingle.AnimScript.DeadEnd.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<137, 0>("step/chara/enemy/landiasingle/Model", "LandiaSingle", 7, T_NODE_NAMES, 19, T_ANIM_ENTRIES, 22, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/landiasingle/Motion";
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<137, 0>("step/chara/enemy/landiasingle/ModelEx", "LandiaSingle", 7, T_NODE_NAMES, 19, T_ANIM_ENTRIES, 22, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/landiasingle/Motion";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::landiasingle
