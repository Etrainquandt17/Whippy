#include "scn/step/enemy/armordee/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace armordee {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 }, { "Fall", 0 }, { "Landing", 0 }, { "Move", 0 }, { "Damage", 0 }, { "DamageEtc", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },     { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { "ArmorDee.AnimScript.Landing.Exec", 0, 0, 0, 0 }, { "ArmorDee.AnimScript.Walk.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },     { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },     { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<8, 0>("step/chara/enemy/ArmorDee", "Armordee", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& HalcandleCreate() {
    return ModelDescUtil::CreateTmpl<86, 0>("step/chara/enemy/HalcandleArmorDee", "HalcandleArmorDee", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::armordee
