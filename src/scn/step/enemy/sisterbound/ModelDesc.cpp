#include "scn/step/enemy/sisterbound/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace sisterbound {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CA2UpBodyJ",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Jump", 0 },
    { "JumpStart", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { "SisterBound.AnimScript.Fall.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 2, 0, 0 },
    { "SisterBound.AnimScript.JumpStart.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<37, 0>("step/chara/enemy/SisterBound", "Sisterbound", 2, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::sisterbound
