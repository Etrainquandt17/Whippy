#include "scn/step/enemy/fattybufferwater/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace fattybufferwater {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "AllJ",
    "WnWaterM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 4, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<127, 0>("step/weapon/fattybuffer/Watermain", "FattyBufferWater", 3, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::fattybufferwater
