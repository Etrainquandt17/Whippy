#include "scn/step/boss/goliath/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"
#include "scn/step/boss/goliath/DynamicsDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace goliath {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "RotL",
    "UpBodyControlJ",
    "LElbowControlJ",
    "LHandJ",
    "RHandJ",
    "LHaveL",
    "RHaveL",
    "HairBaseDJ",
    "BodyM",
    "CA1HipJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Appear", 0 },
    { "LPunchStart", 0 },
    { "LPunchCharge", 0 },
    { "LPunch", 0 },
    { "LPunchAfter", 0 },
    { "LPunchAfterEnd", 0 },
    { "JumpStart", 0 },
    { "JumpStart2", 0 },
    { "Jump", 0 },
    { "BallJump", 0 },
    { "LWallJumpStart", 0 },
    { "LWallJumpStartLong", 0 },
    { "LWallJump", 0 },
    { "LWallLanding", 0 },
    { "LWallWait", 0 },
    { "LWallClimbStart", 0 },
    { "LWallClimb", 0 },
    { "LWallClimbEnd", 0 },
    { "LWallThrow", 0 },
    { "RWallJumpStart", 0 },
    { "RWallJumpStartLong", 0 },
    { "RWallJump", 0 },
    { "RWallLanding", 0 },
    { "RWallWait", 0 },
    { "RWallClimbStart", 0 },
    { "RWallClimb", 0 },
    { "RWallClimbEnd", 0 },
    { "RWallThrow", 0 },
    { "HipIceBigJumpStart", 0 },
    { "HipIceJump", 0 },
    { "Top", 0 },
    { "TopRolling", 0 },
    { "TopRolling", 0 },
    { "HipAttackLandingStart", 0 },
    { "HipAttackLanding", 0 },
    { "HipAttackLandingEnd", 0 },
    { "Damage", 0 },
    { "DamageFallStart", 0 },
    { "DamageFall", 0 },
    { "GroundWallJumpStart", 0 },
    { "GroundLWallJump", 0 },
    { "GroundLWallJumpLoop", 0 },
    { "GroundRWallJump", 0 },
    { "GroundRWallJumpLoop", 0 },
    { "GroundPunchStart", 0 },
    { "GroundPunch", 0 },
    { "GroundPunchEnd", 0 },
    { "LBlizzardStart", 0 },
    { "LBlizzardCharge", 0 },
    { "LBlizzard", 0 },
    { "LBlizzardEnd", 0 },
    { "RBlizzardStart", 0 },
    { "RBlizzardCharge", 0 },
    { "RBlizzard", 0 },
    { "RBlizzardEnd", 0 },
    { "Rocket", 0 },
    { "LRocketCharge", 0 },
    { "RRocketCharge", 0 },
    { "DamageLStart", 0 },
    { "DamageLLanding", 0 },
    { "DamageLEnd", 0 },
    { "HipIceJumpStart", 0 },
    { "HipIceJump", 0 },
    { "HipIceBigJumpStart", 0 },
    { "HipIceBigJump", 0 },
    { "BeamBallS", 0 },
    { "BeamBallM", 0 },
    { "BeamBallL", 0 },
    { "AngryHair", 0 },
    { "NormalHair", 0 },
    { "AngryEyeOpen", 0 },
    { "DeathEye", 0 },
    { "EyeClose", 0 },
    { "NormalEyeOpen", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "Goliath.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "Goliath.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.AppearFall.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.PunchCharge.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Punch.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.WallWait.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.WallJumpStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.WallJump.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.WallClimb.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.WallThrow.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.SwoopStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.SwoopRise.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.SwoopFall.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.SwoopLanding.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.SwoopRotateLanding.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.DeadSmash.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.DeadFall.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.GroundPunch.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.GroundChangeStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.GroundChange.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.GroundChangeLanding.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.BlizzardStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.BlizzardCharge.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Blizzard.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Blizzard.ExecEx", 0, 0, 0, 0 },
    { "Goliath.AnimScript.JumpFarHeroStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.JumpFarHero.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Rocket.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.RocketEnd.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.RocketCharge.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleJump1.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleJump2Start.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleJump2.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleBigJumpStart.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleBigJump.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.FallIcicleBigLanding.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.EnergyBallJump.Exec", 0, 0, 0, 0 },
    { "Goliath.AnimScript.EnergyBallCharge.ExecS", 0, 0, 0, 0 },
    { "Goliath.AnimScript.EnergyBallCharge.ExecM", 0, 0, 0, 0 },
    { "Goliath.AnimScript.EnergyBallCharge.ExecL", 0, 0, 0, 0 },
    { "Goliath.AnimScript.EnergyBallThrow.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<13, 0, 0>(
        isExtra ? "step/chara/enemy/goliath/ModelEx" : "step/chara/enemy/goliath/Model", "step/chara/enemy/goliath/Motion", "Goliath", 12,
        T_NODE_NAMES, 77, T_ANIM_ENTRIES, 48, T_SCRIPT_ENTRIES);
    desc._70[3] = reinterpret_cast<u32>(&DynamicsDesc::Create(false));
    desc.mModel._40 = 3;
    return desc;
}

}

}}}}  // namespace scn::step::boss::goliath
