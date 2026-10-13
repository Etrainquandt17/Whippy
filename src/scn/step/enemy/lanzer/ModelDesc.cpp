#include "scn/step/enemy/lanzer/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace lanzer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Spear2J",
    "Spear3J",
    "SpearPointL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
    { "AttackStart", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "Lanzer.AnimScript.Front.Exec", 0, 0, 0, 0 },
    { "Lanzer.AnimScript.Stay.Exec", 0, 0, 0, 0 },
    { "Lanzer.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<50, 0>("step/chara/enemy/Lanzer", "Lanzer", 4, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
