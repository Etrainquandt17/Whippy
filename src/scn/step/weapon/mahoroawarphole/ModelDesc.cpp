#include "scn/step/weapon/mahoroawarphole/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RipL",
    "RipM",
    "RipBgM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "WarpHoleParaLowperStart", 0 },
    { "WarpHoleEnemyCallStart", 0 },
    { "WarpHoleLoop", 0 },
    { "WarpHoleEnd", 0 },
    { "WarpHoleTexture", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<101>("step/weapon/mahoroabattle1/WarpHole", "MahoroaWarpHole", 4, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 4, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::weapon::mahoroawarphole
