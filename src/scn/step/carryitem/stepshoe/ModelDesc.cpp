#include "scn/step/carryitem/stepshoe/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/carryitem/ModelDescUtil.h"

namespace scn {
namespace step {
namespace carryitem {
namespace stepshoe {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RideL",
    "ScaleControlJ",
    "Star1M",
    "AllJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "JumpLowStart", 0 },
    { "JumpLow", 0 },
    { "JumpLowEnd", 0 },
    { "JumpHightStart", 0 },
    { "JumpHigh", 0 },
    { "JumpHightFall", 0 },
    { "JumpHightLanding", 0 },
    { "FallHit", 0 },
    { "EnptyWait", 0 },
    { "SafetyColor", 0 },
    { "DangerousColor", 0 },
    { "MostDangerousColor", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 10, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 11, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<7,0>("step/item/StepShoe", "StepShoe", 5, T_NODE_NAMES, 12, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
    desc.mModel._44[0] = 0x1000;
    ModelDescUtil::Set_4C(desc, true);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::carryitem::stepshoe
