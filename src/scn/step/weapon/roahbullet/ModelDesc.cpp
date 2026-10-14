#include "scn/step/weapon/roahbullet/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace roahbullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PtclL",
    "RotControlL",
    "RotAnimL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Main", 0 },
    { "TpaRedMain", 0 },
    { "TpaBlueMain", 0 },
    { "TpaYellowMain", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<71>("step/weapon/roah/Energysphere", "RoahBullet", 4, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<71>("step/weapon/roahex/Energysphere", "RoahBullet", 4, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::weapon::roahbullet
