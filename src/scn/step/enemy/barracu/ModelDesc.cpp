#include "scn/step/enemy/barracu/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace barracu {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "CatchL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Move", 0 },
    { "MoveLoop", 0 },
    { "Move2", 0 },
    { "Move3", 0 },
    { "MoveTurn1", 0 },
    { "MoveTurn2", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "AttackStart", 0 },
    { "AttackLoop", 0 },
    { "AttackEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 4, 0, 0 },
    { "Barracu.AnimScript.Swim.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { "Barracu.AnimScript.Bite.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 4, 0, 0 },
    { "Barracu.AnimScript.Escape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<59, 0>("step/chara/enemy/Barracu", "Barracu", 3, T_NODE_NAMES, 12, T_ANIM_ENTRIES, 13, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
