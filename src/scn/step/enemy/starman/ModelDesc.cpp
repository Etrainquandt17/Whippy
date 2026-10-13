#include "scn/step/enemy/starman/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace starman {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HipJ",
    "LKneeJ",
    "RKneeJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "HiJumpStart", 0 },
    { "Flight", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { "Starman.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { "Starman.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "Starman.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "Starman.AnimScript.HiJumpStart.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 8, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<28, 0>("step/chara/enemy/Starman", "Starman", 4, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
