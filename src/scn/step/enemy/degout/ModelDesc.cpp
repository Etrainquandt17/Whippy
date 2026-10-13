#include "scn/step/enemy/degout/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace degout {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Chase", 0 },
    { "HitStart", 0 },
    { "HitSpin", 0 },
    { "HitEnd", 0 },
    { "Move", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<48, 0>("step/chara/enemy/Degout", "Degout", 1, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateChaseKey() {
    return ModelDescUtil::CreateTmpl<88, 0>("step/chara/enemy/ChaseKeyDegout", "ChaseKeyDegout", 1, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
