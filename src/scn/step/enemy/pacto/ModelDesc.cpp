#include "scn/step/enemy/pacto/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace pacto {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TopL",
    "L1MouthJ",
    "R1MouthJ",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "AttackOpen", 0 },
    { "AttackClose", 0 },
    { "AttackChew", 0 },
    { "AttackSpit", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<13, 0>("step/chara/enemy/Pacto", "Pacto", 5, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateCloud() {
    return ModelDescUtil::CreateTmpl<76, 0>("step/chara/enemy/Pacloud", "Pacloud", 5, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
