#include "scn/step/enemy/rocky/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace rocky {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "CA1HipJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "StoneFall", 0 },
    { "StoneLanding", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "MoveStart", 0 },
    { "MoveEnd", 0 },
    { "StoneStart", 0 },
    { "StoneAttack", 0 },
    { "Stream", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 10, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<26, 0>("step/chara/enemy/Rocky", "Rocky", 3, T_NODE_NAMES, 11, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
