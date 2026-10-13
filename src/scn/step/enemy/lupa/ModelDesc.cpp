#include "scn/step/enemy/lupa/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace lupa {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Walk", 0 },
    { "Attack", 0 },
    { "Loop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<83, 0>("step/chara/enemy/Lupa", "Lupa", 1, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::enemy::lupa
