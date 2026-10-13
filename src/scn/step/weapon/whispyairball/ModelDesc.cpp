#include "scn/step/weapon/whispyairball/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace whispyairball {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Loop", 0 },
    { "BigLoop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<12>("step/weapon/whispy/breath/Model", "WhispyAirBall", 1, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 2, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc._8 = "step/weapon/whispy/breath/Motion";
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<12>("step/weapon/whispy/breath/ModelEx", "WhispyAirBall", 1, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 2, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc._8 = "step/weapon/whispy/breath/Motion";
    return desc;
}

}

}
}
}
}
