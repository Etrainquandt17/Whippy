#include "scn/step/enemy/flamer/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace flamer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "BodyJ",
    "Rot2L",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "RMove", 0 },
    { "LMove", 0 },
    { "MoveStart", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 8, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 8, 0, 0 },
    { "Flamer.AnimScript.Chase.Exec", 0, 0, 0, 0 },
    { "Flamer.AnimScript.AttackR.Exec", 0, 0, 0, 0 },
    { "Flamer.AnimScript.AttackL.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<23, 0>("step/chara/enemy/Flamer", "Flamer", 3, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 12, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::flamer
