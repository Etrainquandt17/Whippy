#include "scn/step/weapon/roahoar/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace roahoar {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<72>("step/weapon/roah/Oar", "RoahOar", 2, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 2, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<72>("step/weapon/roahex/Oar", "RoahOar", 2, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 2, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::roahoar
