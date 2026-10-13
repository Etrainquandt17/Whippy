#include "scn/step/enemy/sparky/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sparky {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "LSphereM",
    "RSphereM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
    { "Spark", 0 },
    { "SparkEnd", 0 },
    { "SparkStart", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 2, 0, 0 },
    { "Sparky.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<18, 0>("step/chara/enemy/Sparky", "Sparky", 4, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 13, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::sparky
