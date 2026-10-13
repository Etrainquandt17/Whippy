#include "scn/step/enemy/squishy/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace squishy {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Move", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "Swim", 0 },
    { "Swim2Start", 0 },
    { "Swim2", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "Squishy.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Squishy.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 12, 0, 0 },
    { "Squishy.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
    { "Squishy.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { "Squishy.AnimScript.Swim.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 10, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<60, 0>("step/chara/enemy/Squishy", "Squishy", 1, T_NODE_NAMES, 11, T_ANIM_ENTRIES, 13, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::squishy
