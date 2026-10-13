#include "scn/step/enemy/sodory/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sodory {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Rot1L",
    "Rot2L",
    "RotateL",
    "EyeL",
    "HitPoint1L",
    "HitPoint2L",
    "HitPoint3L",
    "Foot1J",
    "Foot2J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "FlightWait", 0 },
    { "Attack", 0 },
    { "GroundAttackStart", 0 },
    { "GroundAttack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "Sodory.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { "Sodory.AnimScript.GroundAttack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<68, 0>("step/chara/enemy/Sodory", "Sodory", 10, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
