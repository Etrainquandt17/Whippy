#include "scn/step/enemy/sirkibble/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sirkibble {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "SirkibbleM",
    "HeadCutterM",
    "LItemCutterM",
    "RItemCutterM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "CutterThrow", 0 },
    { "CutterCatch", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "AirCutterThrow", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 10, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 6, 0, 0 },
    { "SirKibble.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 10, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<0, 0>("step/chara/enemy/Sirkibble", "Sirkibble", 5, T_NODE_NAMES, 11, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
