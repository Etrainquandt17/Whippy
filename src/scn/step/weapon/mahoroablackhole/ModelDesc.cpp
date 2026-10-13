#include "scn/step/weapon/mahoroablackhole/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackhole {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RipL",
    "RipM",
    "RipBgM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
    { "End", 0 },
    { "Texture", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<92>("step/weapon/mahoroabattle1/BlackWarpHole", "MahoroaBlackHole", 4, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 3, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<92>("step/weapon/mahoroabattle1/ExBlackWarpHole", "MahoroaBlackHole", 4, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 3, T_SCRIPT_ENTRIES);
    desc._8 = "step/weapon/mahoroabattle1/BlackWarpHole";
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::weapon::mahoroablackhole
