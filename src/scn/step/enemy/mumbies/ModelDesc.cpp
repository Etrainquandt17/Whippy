#include "scn/step/enemy/mumbies/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace mumbies {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Tracking", 0 },
    { "TrackingStart", 0 },
    { "TrackingEnd", 0 },
    { "Endure", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<39, 0>("step/chara/enemy/Mumbies", "Mumbies", 1, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
