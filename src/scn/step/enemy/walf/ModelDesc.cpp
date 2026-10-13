#include "scn/step/enemy/walf/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace walf {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "EffectL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "Fall", 0 },
    { "Landing", 0 },
    { "Walk", 0 },
    { "DamageHi1", 0 },
    { "DamagePose", 0 },
    { "WalkWaterStart", 0 },
    { "WalkWater", 0 },
    { "Kneebend", 0 },
    { "Jump", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 10, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 2, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 8, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 4, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 2, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 6, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 7, 8, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 8, 4, 0, 0 },
    { "Walf.AnimScript.Jump.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<78, 0>("step/chara/enemy/Walf", "Walf", 2, T_NODE_NAMES, 10, T_ANIM_ENTRIES, 11, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::walf
