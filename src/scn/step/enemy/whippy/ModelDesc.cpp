#include "scn/step/enemy/whippy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace whippy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PJointJ",
    "TailJ8",
    "TailJ7",
    "TailJ6",
    "TailJ5",
    "TailJ4",
    "TailJ3",
    "TailJ2",
    "TailJ1",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "AttackStart", 0 },
    { "AttackCharge", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { "Whippy.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<12, 0>("step/chara/enemy/Whippy", "Whippy", 10, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
