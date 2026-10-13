#include "scn/step/enemy/tsukikage/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "WaitLeft", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Damage", 0 },
    { "DamageEtc", 0 },
    { "JumpStart", 0 },
    { "Jump", 0 },
    { "AttackLeft", 0 },
    { "WaitWallLeft", 0 },
    { "WaitWallRight", 0 },
    { "AttackWallLeft", 0 },
    { "AttackWallRight", 0 },
    { "WaitRight", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 6, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 3, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 5, 8, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 8, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 9, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 10, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 11, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 12, 6, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<52, 0>("step/chara/enemy/Tsukikage", "Tsukikage", 1, T_NODE_NAMES, 13, T_ANIM_ENTRIES, 15, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::tsukikage
