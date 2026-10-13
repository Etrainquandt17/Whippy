#include "scn/step/enemy/pierce/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "SpearFrontL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Move", 0 },
    { "MoveStart", 0 },
    { "MoveEnd", 0 },
    { "AttackL", 0 },
    { "AttackR", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 10, 0, 0 },
    { "Pierce.AnimScript.MoveStart.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { "Pierce.AnimScript.AttackL.Exec", 0, 0, 0, 0 },
    { "Pierce.AnimScript.AttackR.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<62, 0>("step/chara/enemy/Pierce", "Pierce", 2, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
