#include "scn/step/enemy/twister/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace twister {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TransL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "Move1", 0 },
    { "Move2", 0 },
    { "Move2Start", 0 },
    { "Move2End", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<29, 0>("step/chara/enemy/Twister", "Twister", 2, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::twister
