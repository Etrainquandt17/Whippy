#include "scn/step/enemy/metalgeneralthunder/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralthunder {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MetalGeneralThunder.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralThunder.AnimScript.Attack.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<125, 0>("step/weapon/metalgeneral/Bomb", "MetalGeneralThunder", 1, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::metalgeneralthunder
