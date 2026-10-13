#include "scn/step/enemy/blipper/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace blipper {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait2", 0 },
    { "WaitFall", 0 },
    { "WaitLanding", 0 },
    { "WaitJump", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "WaitStart", 0 },
    { "Move", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<33, 0>("step/chara/enemy/Blipper", "Blipper", 2, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
