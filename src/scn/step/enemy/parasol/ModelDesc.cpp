#include "scn/step/enemy/parasol/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace parasol {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyM",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Parasol", 0 },
    { "ParasolLanding", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Parasol", 0 },
    { "ParasolLanding", 0 },
    { "ParasolOut", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<113, 0>("step/chara/enemy/Parasol", "Parasol", 3, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::parasol
