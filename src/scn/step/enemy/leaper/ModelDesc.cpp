#include "scn/step/enemy/leaper/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace leaper {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Attack", 0 },
    { "Loop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "Leaper.AnimScript.Fly.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<84, 0>("step/chara/enemy/Leaper", "Leaper", 1, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::enemy::leaper
