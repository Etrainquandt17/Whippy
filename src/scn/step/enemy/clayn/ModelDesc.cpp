#include "scn/step/enemy/clayn/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "RotL",
    "Chest0J",
    "Chest1J",
    "Chest2J",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "HideWait", 0 },
    { "Appear", 0 },
    { "Disappear", 0 },
    { "WaitEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "Clayn.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "Clayn.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "Clayn.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<61, 0>("step/chara/enemy/Clayn", "Clayn", 6, T_NODE_NAMES, 9, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::clayn
