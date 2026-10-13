#include "scn/step/weapon/starshotlv3/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv3 {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotControlLL",
    "PtclL",
    "SmallStarM",
    "SmallStar2M",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<2>("step/weapon/normal/BigStrongStar", "StarShotLv3", 5, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::starshotlv3
