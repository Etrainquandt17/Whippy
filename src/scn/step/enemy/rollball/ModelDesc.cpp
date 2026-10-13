#include "scn/step/enemy/rollball/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace rollball {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
};

const char* T_NODE_NAMES_IRON[] = {
    "TopL",
    "RockCrackM1",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "Wait", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<38, 0>("step/chara/enemy/BallRock", "Ballrock", 2, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateIron() {
    return ModelDescUtil::CreateTmpl<56, 0>("step/chara/enemy/BallIron", "BallIron", 2, T_NODE_NAMES_IRON, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateIce() {
    return ModelDescUtil::CreateTmpl<91, 0>("step/chara/enemy/BallIce", "BallIce", 2, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateLava() {
    return ModelDescUtil::CreateTmpl<99, 0>("step/chara/enemy/BallLava", "BallLava", 2, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::rollball
