#include "scn/step/enemy/barbar/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace barbar {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "TransL",
    "UpMouthJ",
    "CA4BodyJ",
    "CollisionL",
    "CA5HeadJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Attack", 0 },
    { "AttackLoop", 0 },
    { "AttackEnd", 0 },
    { "AttackMistake", 0 },
    { "AttackStepback", 0 },
    { "AttackStart", 0 },
    { "Hiding", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<58, 0>("step/chara/enemy/Barbar", "Barbar", 7, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateIron() {
    return ModelDescUtil::CreateTmpl<77, 0>("step/chara/enemy/IronBarbar", "IronBarbar", 7, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
