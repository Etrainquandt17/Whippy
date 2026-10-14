#include "scn/step/enemy/metalgeneralpatriot/ModelDesc.h"

#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralpatriot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PtclL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralPatriot.AnimScript.Fly.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralPatriot.AnimScript.Appear.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<124, 0>("step/weapon/metalgeneral/Patriotmissile", "MetalGeneralPatriot", 2, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<124, 0>("step/weapon/metalgeneralex/Patriotmissileex", "MetalGeneralPatriot", 2, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::metalgeneralpatriot
