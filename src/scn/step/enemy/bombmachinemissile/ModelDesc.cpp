#include "scn/step/enemy/bombmachinemissile/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bombmachinemissile {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "AnimL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Flight", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<133, 0>("step/chara/enemy/Missile", "BombMachineMissile", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
