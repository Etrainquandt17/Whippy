#include "scn/step/carryitem/mtomatobox/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/carryitem/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace carryitem {
namespace mtomatobox {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Open", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<2,0>("step/item/MTomatoBox", "MTomatoBox", 1, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 2, T_SCRIPT_ENTRIES);
    desc.mModel._44[0] = 0x1000;
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::carryitem::mtomatobox
