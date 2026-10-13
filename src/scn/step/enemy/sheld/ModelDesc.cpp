#include "scn/step/enemy/sheld/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sheld {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyM",
    "ShellM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
    { "Dash", 0 },
    { "DashEnd", 0 },
    { "DashStart", 0 },
    { "ShellDamage", 0 },
    { "Escape", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { "Sheld.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { "Sheld.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "Sheld.AnimScript.Dash.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 10, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 4, 0, 0 },
    { "Sheld.AnimScript.Escape.Exec", 0, 0, 0, 0 },
    { "Sheld.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "Sheld.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<49, 0>("step/chara/enemy/Sheld", "Sheld", 3, T_NODE_NAMES, 13, T_ANIM_ENTRIES, 16, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::sheld
