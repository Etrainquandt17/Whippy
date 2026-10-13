#include "scn/step/enemy/carrydee/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace carrydee {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CarryL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait_normal", 0 },
    { "Fall_Normal", 0 },
    { "Landing_Normal", 0 },
    { "Walk_Normal", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "Run", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "CarryDee.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "CarryDee.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 4, 0, 0 },
    { "CarryDee.AnimScript.Jump.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 12, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<90, 0>("step/chara/enemy/CarryDee", "CarryDee", 2, T_NODE_NAMES, 13, T_ANIM_ENTRIES, 13, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::carrydee
