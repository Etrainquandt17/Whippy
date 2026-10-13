#include "scn/step/enemy/doubtersnake/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubtersnake {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Jump", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<110, 0>("step/chara/enemy/doubtersnake/Model", "DoubterSnake", 1, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/doubtersnake/Motion";
    return desc;
}

chara::ModelDesc& CreateYellow() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<111, 0>("step/chara/enemy/doubtersnake/ModelYellow", "DoubterYellowSnake", 1, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/doubtersnake/Motion";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::doubtersnake
