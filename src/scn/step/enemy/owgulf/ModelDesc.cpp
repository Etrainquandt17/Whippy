#include "scn/step/enemy/owgulf/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Fly", 0 },
    { "FlightWait", 0 },
    { "AttackSmall", 0 },
    { "AttackBig", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<47, 0>("step/chara/enemy/Owgulf", "Owgulf", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::owgulf
