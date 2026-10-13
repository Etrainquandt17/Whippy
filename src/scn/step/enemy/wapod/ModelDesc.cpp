#include "scn/step/enemy/wapod/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace wapod {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HipJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Appear", 0 },
    { "Return", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<129, 0>("step/chara/enemy/Wapod", "Wapod", 2, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::enemy::wapod
