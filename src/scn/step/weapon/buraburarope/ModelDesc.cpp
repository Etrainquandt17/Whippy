#include "scn/step/weapon/buraburarope/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace buraburarope {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA1RopeJ",
    "CA2RopeJ",
    "CA3RopeJ",
    "CA4RopeJ",
    "CA5RopeJ",
    "CA6RopeJ",
    "CA7RopeJ",
    "CA8RopeJ",
    "GripL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "RopeDeath", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<79>("step/weapon/rope/Swingrope", "Swingrope", 10, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
