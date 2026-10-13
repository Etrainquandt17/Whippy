#include "scn/step/enemy/hothead/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace hothead {

namespace {

const char* T_NODE_NAMES_NORMAL[] = {
    "TopL",
    "TopL",
    "FireLPtclL",
    "MouthL",
    "CA4FaceJ",
};

const char* T_NODE_NAMES_SUPER[] = {
    "TopL",
    "TopL",
    "FireLPtclL",
    "MouthL",
    "StarL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Attack1Start", 0 },
    { "Attack1", 0 },
    { "Attack1End", 0 },
    { "Attack2", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { "HotHead.AnimScript.Attack.Exec", 0, 0, 0, 0 },
    { "HotHead.AnimScript.SuperAppear.Exec", 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 9, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& CreateNormal() {
    return ModelDescUtil::CreateTmpl<5, 0>("step/chara/enemy/Hothead", "Hothead", 5, T_NODE_NAMES_NORMAL, 10, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateSuper() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<5, 1>("step/chara/enemy/Hothead", "Hothead", 5, T_NODE_NAMES_SUPER, 10, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
    desc._4 = "step/chara/enemy/SpHothead";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::hothead
