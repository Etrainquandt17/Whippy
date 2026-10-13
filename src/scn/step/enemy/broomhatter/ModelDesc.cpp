#include "scn/step/enemy/broomhatter/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace broomhatter {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Hoki3J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Move2", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "SlopeStart", 0 },
    { "SlopeLoop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { "BroomHatter.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 10, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 10, 0, 0 },
    { "BroomHatter.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "BroomHatter.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<20, 0>("step/chara/enemy/Broom", "Broomhatter", 2, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}
}
}
}
