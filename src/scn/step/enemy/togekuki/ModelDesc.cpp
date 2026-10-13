#include "scn/step/enemy/togekuki/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace togekuki {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TopL",
    "NikuHeadM",
    "Niku8M",
    "Niku7M",
    "Niku6M",
    "Niku5M",
    "Niku4M",
    "Niku3M",
    "Niku2M",
    "Niku1M",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Wait", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<11, 0>("step/chara/enemy/Togekuki", "Togekuki", 11, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::togekuki
