#include "scn/step/enemy/whispyapple/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace whispyapple {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Appear", 0 },
    { "FallSign", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { "WhispyApple.AnimScript.Appear.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<106, 0>("step/chara/enemy/whispyapple/Model", "WhispyApple", 1, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/whispyapple/Motion";
    return desc;
}

chara::ModelDesc& CreatePoison() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<107, 0>("step/chara/enemy/whispyapple/ModelPoison", "WhispyApplePoison", 1, T_NODE_NAMES, 3, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/whispyapple/Motion";
    return desc;
}

}

}
}
}
}
