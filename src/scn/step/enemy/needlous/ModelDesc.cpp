#include "scn/step/enemy/needlous/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace needlous {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotL",
    "RoundL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "AttackEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { "Needlous.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "Needlous.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<19, 0>("step/chara/enemy/Needlous", "Needlous", 3, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::needlous
