#include "scn/step/boss/hrd3/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/math/Vector3.h"
#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace hrd3 {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "CA2UnderBodyS",
    "CA3BodytopS",
    "CA6CannonS",
    "CA7CannonS",
    "CB1HeadshaftS",
    "HelmetControlL",
    "DedeRotS",
    "CC1UnderGearS",
    "CD1UnderGearS",
    "CE1UnderGearS",
    "LA2ArmS",
    "LA3ElbowS",
    "LA4HandS",
    "LB1WristS",
    "LB3FingerS",
    "LMufflerS",
    "LMufflerPtclL",
    "LPipeS",
    "LSidemufflerS",
    "LSidemufflerPtclL",
    "RA2ArmS",
    "RA3ElbowS",
    "RA4HandS",
    "RA5DrilS",
    "RMufflerS",
    "RMufflerPtclL",
    "RPipeS",
    "RSidemufflerS",
    "RSidemufflerPtclL",
    "LBustcoreM",
    "LBustM",
    "LShouldecorerM",
    "LHandM",
    "RBustcoreM",
    "RBustM",
    "RShouldercoreM",
    "DorilM",
    "UnderGearM",
    "FTankM",
    "HipneedleM",
    "LBodyunderM",
    "RBodyunderM",
    "BustshadowM",
    "BrowM",
    "EyeshadowM",
    "HeadM",
    "MouthM",
    "CBustCoreM",
    "LArmM",
    "LShoulderM",
    "RArmM",
    "RShoulderM",
    "RadiatorM",
    "LHaramakiM",
    "RHaramakiM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Appear", 0 },
    { "DeathLoop", 0 },
    { "Death", 0 },
    { "Damage", 0 },
    { "BeamStart", 0 },
    { "Beam", 0 },
    { "BeamEnd", 0 },
    { "PressRiseStart", 0 },
    { "PressRise", 0 },
    { "PressFall", 0 },
    { "PressLanding", 0 },
    { "PunchL", 0 },
    { "PunchR", 0 },
    { "ArmSpinStart", 0 },
    { "ArmSpin", 0 },
    { "AirSpinEnd", 0 },
    { "BodyPressRiseStart", 0 },
    { "BodyPressRise", 0 },
    { "BodyPress", 0 },
    { "BodyPressLanding", 0 },
    { "BodyPressEnd", 0 },
    { "LaserEyeStart", 0 },
    { "LaserEyeLoop", 0 },
    { "LaserEyeEnd", 0 },
    { "Idling", 0 },
    { "DorillLoop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "HRD3.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "HRD3.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.AppearFall.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Punch.ExecLeft", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Punch.ExecRight", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Punch.ExecTripleLeft", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Punch.ExecTripleRight", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PunchFar.ExecLeft", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PunchFar.ExecRight", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Beam.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.BeamEnd.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Rise.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PressSearch.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PressFall.ExecS", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PressFall.ExecL", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PressLanding.ExecS", 0, 0, 0, 0 },
    { "HRD3.AnimScript.PressLanding.ExecL", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Lariat.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.Lariat.ExecWithAttack", 0, 0, 0, 0 },
    { "HRD3.AnimScript.LariatFar.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.LariatEnd.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.FlyingBodyPressRise.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.FlyingBodyPressFall.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.FlyingBodyPressEnd.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.FallFar.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.BeamFar.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.BeamFarEnd.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.MissileFar.Exec", 0, 0, 0, 0 },
    { "HRD3.AnimScript.SwingArmFar.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<19, 0, 0>(
        "step/chara/enemy/hrd3/Model", "step/chara/enemy/hrd3/Motion", "HRD3", 57, T_NODE_NAMES, 27, T_ANIM_ENTRIES, 35,
        T_SCRIPT_ENTRIES
    );
    desc._c = hel::math::Vector3(0.0f, 4.8f, 0.0f);
    desc.mModel._40 = 3;
    return desc;
}

}

}}}}  // namespace scn::step::boss::hrd3
