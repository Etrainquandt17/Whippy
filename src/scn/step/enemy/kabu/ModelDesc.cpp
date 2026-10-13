#include "scn/step/enemy/kabu/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace kabu {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },      { "Fall", 0 }, { "Landing", 0 }, { "Wait", 0 },  { "Damage", 0 }, { "DamageEtc", 0 },
    { "JumpStart", 0 }, { "Jump", 0 }, { "Move", 0 },    { "Warp1", 0 }, { "Warp2", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 6, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 10, 2, 0, 0 },
    { "Kabu.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "Kabu.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<41, 0>("step/chara/enemy/Kabu", "Kabu", 2, T_NODE_NAMES, 11, T_ANIM_ENTRIES, 14, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::kabu
