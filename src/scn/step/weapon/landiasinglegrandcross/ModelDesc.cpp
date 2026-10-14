#include "scn/step/weapon/landiasinglegrandcross/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace landiasinglegrandcross {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotControlL",
    "LandiaConst1J",
    "LandiaConst2J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
    { "End", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<107>("step/weapon/landia/Grandcross", "LandiaSingleGrandCross", 4, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 3, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::landiasinglegrandcross
