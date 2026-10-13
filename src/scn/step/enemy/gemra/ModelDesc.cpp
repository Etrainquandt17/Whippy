#include "scn/step/enemy/gemra/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace gemra {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyJ",
    "BeamBaseJ",
    "Beam1J",
    "Beam2J",
    "Beam3J",
    "Beam4J",
    "Beam5J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "FlightWait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 4, 0, 0 },
    { "Gemra.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<54, 0>("step/chara/enemy/Gemra", "Gemra", 8, T_NODE_NAMES, 4, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
