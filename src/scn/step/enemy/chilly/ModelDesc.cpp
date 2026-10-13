#include "scn/step/enemy/chilly/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace chilly {

namespace {

const char* T_NODE_NAMES_NORMAL[] = {
    "TopL",
    "TopL",
};

const char* T_NODE_NAMES_SUPER[] = {
    "TopL",
    "StarL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Wait2", 0 },
    { "Move", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "Blizzard", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 12, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 4, 0, 0 },
    { "Chilly.AnimScript.SuperAppear.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& CreateNormal() {
    return ModelDescUtil::CreateTmpl<51, 0>("step/chara/enemy/Chilly", "Chilly", 2, T_NODE_NAMES_NORMAL, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

chara::ModelDesc& CreateSuper() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<51, 1>("step/chara/enemy/Chilly", "Chilly", 2, T_NODE_NAMES_SUPER, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
    desc._4 = "step/chara/enemy/SpChilly";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::chilly
