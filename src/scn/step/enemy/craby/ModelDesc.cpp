#include "scn/step/enemy/craby/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace craby {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "LClawAllJ",
    "RClawAllJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Move", 0 },
    { "LAttackStart", 0 },
    { "LAttack", 0 },
    { "LAttackEnd", 0 },
    { "RAttackStart", 0 },
    { "RAttack", 0 },
    { "RAttackEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 12, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { "Craby.AnimScript.LAttack.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
    { "Craby.AnimScript.RAttack.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<75, 0>("step/chara/enemy/Craby", "Craby", 3, T_NODE_NAMES, 12, T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
