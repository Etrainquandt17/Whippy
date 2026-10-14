#include "scn/step/carryitem/prismshield/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/carryitem/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace carryitem {
namespace prismshield {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PrismShieldM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait", 0 },
    { "AttackStart", 0 },
    { "Attack", 0 },
    { "Blue", 0 },
    { "Yellow", 0 },
    { "Red", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
    { gobj::AnimScript::PLAY_ONE_SHOT, 1, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 2, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 3, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 4, 0, 0, 0 },
    { gobj::AnimScript::PLAY_LOOP, 5, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<8,0>("step/item/PrismShield", "PrismShield", 2, T_NODE_NAMES, 6, T_ANIM_ENTRIES, 6, T_SCRIPT_ENTRIES);
    desc.mModel._44[0] = 0xA00;
    desc.mModel._40 = 2;
    ModelDescUtil::Set_4C(desc, true);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::carryitem::prismshield
