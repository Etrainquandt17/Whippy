#include "scn/step/carryitem/cracker/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/carryitem/ModelDescUtil.h"

namespace scn {
namespace step {
namespace carryitem {
namespace cracker {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ShootL",
    "StarL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Shoot", 0 },
    { "Crash", 0 },
    { "Blue", 0 },
    { "Yellow", 0 },
    { "Red", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_ONE_SHOT, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<4,0>("step/item/Cracker", "Cracker", 3, T_NODE_NAMES, 5, T_ANIM_ENTRIES, 5, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    desc.mModel._44[0] = 0x1000;
    ModelDescUtil::Set_4C(desc, true);
    desc.mModel._40 = 2;
    return desc;
}

}

}}}}  // namespace scn::step::carryitem::cracker
