#include "scn/step/enemy/elec/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace elec {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "EyeJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "RMove", 0 },
    { "RMove", 0 },
    { "LMove", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "MoveStart", 0 },
    { "Move", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { "Elec.AnimScript.Chase.Exec", 0, 0, 0, 0 },
    { "Elec.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<65, 0>("step/chara/enemy/Elec", "Elec", 3, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
