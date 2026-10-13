#include "scn/step/enemy/pluid/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace pluid {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "Pluid.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { "Pluid.AnimScript.Landing.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { "Pluid.AnimScript.Damage.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<53, 0>("step/chara/enemy/Pluid", "Pluid", 1, T_NODE_NAMES, 8, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::pluid
