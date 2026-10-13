#include "scn/step/enemy/cappy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CappyM",
    "CappyhatM",
    "ArmM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },      { "Fall", 0 },   { "Landing", 0 },  { "Wait", 0 },         { "Damage", 0 },
    { "DamageEtc", 0 }, { "KasaUp", 0 }, { "ZHatLose", 0 }, { "ZHatLoseLoop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },     { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 }, { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },     { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },     { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 }, { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<4, 0>("step/chara/enemy/Cappy", "Cappy", 4, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
