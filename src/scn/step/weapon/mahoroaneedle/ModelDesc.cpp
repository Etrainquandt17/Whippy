#include "scn/step/weapon/mahoroaneedle/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroaneedle {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "SignStart", 0 },
    { "StartLoop", 0 },
    { "KillNeedleStart", 0 },
    { "KillNeedleLoop", 0 },
    { "KillNeedleEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_SUITE, 0, 0, 1, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<77>("step/weapon/mahoroabattle1/KillNeedle", "MahoroaNeedle", 1, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 4, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<77>("step/weapon/mahoroabattle1/ExKillNeedle", "MahoroaNeedle", 1, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 4, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc._8 = "step/weapon/mahoroabattle1/KillNeedle";
    return desc;
}

chara::ModelDesc& Create2() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<78>("step/weapon/mahoroabattle2/KillNeedle", "MahoroaNeedle2", 1, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 4, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& Create2Ex() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<78>("step/weapon/mahoroabattle2/KillNeedleEx", "MahoroaNeedle2", 1, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 4, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::mahoroaneedle
