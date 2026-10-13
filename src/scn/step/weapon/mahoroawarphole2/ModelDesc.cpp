#include "scn/step/weapon/mahoroawarphole2/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace mahoroawarphole2 {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RipL",
    "RipM",
    "RipBgM",
    "joint1",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "WarpHoleStart", 0 },
    { "WarpHoleMain", 0 },
    { "WarpHoleEnd", 0 },
    { "TextureMain", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<142>("step/weapon/mahoroabattle2/WarpHole", "MahoroaWarpHole2", 5, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 3, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc.mModel._40 = 2;
    return desc;
}

}

}
}
}
}
