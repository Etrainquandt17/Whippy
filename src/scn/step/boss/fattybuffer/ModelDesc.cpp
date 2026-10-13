#include "scn/step/boss/fattybuffer/ModelDesc.h"

#include "scn/step/boss/ModelDesc.h"

namespace scn {
namespace step {
namespace boss {
namespace fattybuffer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ReleasePointL",
    "BumpPointL",
    "ControlL",
    "EyeRJ",
    "EyeLJ",
    "CA1WaistJ",
    "CA3NeckJ",
    "MouthUpJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "AppearStart", 0 },
    { "AppearEnd", 0 },
    { "TurnR", 0 },
    { "TurnL", 0 },
    { "MoveRStart", 0 },
    { "MoveR", 0 },
    { "MoveLStart", 0 },
    { "MoveL", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "SmJumpStart", 0 },
    { "SmJump", 0 },
    { "SmFall", 0 },
    { "SmLanding", 0 },
    { "WaterStart", 0 },
    { "Water", 0 },
    { "WaterEnd", 0 },
    { "SwellStart", 0 },
    { "Swell", 0 },
    { "Fade", 0 },
    { "BackStart", 0 },
    { "Back", 0 },
    { "BackFall", 0 },
    { "BackLanding", 0 },
    { "Rolling", 0 },
    { "BumpSide", 0 },
    { "BumpStart", 0 },
    { "BumpEnd", 0 },
    { "SwellLanding", 0 },
    { "Death", 0 },
    { "Damage", 0 },
    { "Greeting", 0 },
    { "Attack", 0 },
    { "Hiding", 0 },
    { "HidingEnd", 0 },
    { "BounceTop", 0 },
    { "BounceSide", 0 },
    { "BounceBottom", 0 },
    { "NormalEye", 0 },
    { "AngryEye", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "FattyBuffer.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Dead.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.AppearLong.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Turn.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.MoveForward.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StickRoofJumpStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StampStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StampRise.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StampFall.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StampLanding.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Cannon.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.CannonEnd.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellWait.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellEnd.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBackJumpStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBackJump.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBackJumpLanding.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellRollingAttack.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellRollingWallHit.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellRollingRebound.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellRollingLanding.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBalloonStart.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBalloonMove.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBalloonBound.Exec(int)", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBalloonBound.Exec(int)", 1, 0, 0, 0 },
    { "FattyBuffer.AnimScript.SwellBalloonBound.Exec(int)", 2, 0, 0, 0 },
    { "FattyBuffer.AnimScript.DamageL.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Anger.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteStart.Exec(int)", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteJump.Exec(int)", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteLanding.Exec(int)", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteStart.Exec(int)", 1, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteJump.Exec(int)", 1, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteLanding.Exec(int)", 1, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteStart.Exec(int)", 2, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteJump.Exec(int)", 2, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteLanding.Exec(int)", 2, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteStart.Exec(int)", 3, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteJump.Exec(int)", 3, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteLanding.Exec(int)", 3, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteStart.Exec(int)", 4, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteJump.Exec(int)", 4, 0, 0, 0 },
    { "FattyBuffer.AnimScript.StalactiteLanding.Exec(int)", 4, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Disgorge.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.Hiding.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.HidingEnd.Exec", 0, 0, 0, 0 },
    { "FattyBuffer.AnimScript.AppearJump.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create(u32 level, bool isExtra) {
    chara::ModelDesc& desc = boss::ModelDesc::CreateTmpl<12, 0, 0>(isExtra ? "step/chara/enemy/fattybuffer/ModelEx" : "step/chara/enemy/fattybuffer/Model",
        "step/chara/enemy/fattybuffer/Motion", "FattyBuffer", 9, T_NODE_NAMES, 43, T_ANIM_ENTRIES, 54,
        T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::boss::fattybuffer
