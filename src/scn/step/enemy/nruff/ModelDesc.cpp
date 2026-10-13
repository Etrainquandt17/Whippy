#include "scn/step/enemy/nruff/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace nruff {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "CA3BodyJ",
    "DeeControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Move", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
    { "Nruff.AnimScript.GrandLowperEscapeStart.Exec", 0, 0, 0, 0 },
    { "Nruff.AnimScript.GrandLowperEscape.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<22, 0>("step/chara/enemy/Nruff", "Nruff", 4, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::nruff
