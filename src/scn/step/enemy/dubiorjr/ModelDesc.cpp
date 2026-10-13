#include "scn/step/enemy/dubiorjr/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace dubiorjr {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HipJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<114, 0>("step/chara/enemy/dubiorjr/Model", "DubiorJr", 2, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/dubiorjr/Motion";
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<114, 0>("step/chara/enemy/dubiorjr/ModelEx", "DubiorJr", 2, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/dubiorjr/Motion";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::dubiorjr
