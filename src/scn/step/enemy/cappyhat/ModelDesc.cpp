#include "scn/step/enemy/cappyhat/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace cappyhat {

namespace {

const char* T_NODE_NAMES[] = {
    "ControlL",
    "ControlL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Attack", 0 },
    { "Attack", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 2, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<101, 0>("step/chara/enemy/CappyHat", "CappyHat", 2, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::cappyhat
