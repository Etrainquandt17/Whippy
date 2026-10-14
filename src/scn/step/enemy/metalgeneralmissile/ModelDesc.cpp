#include "scn/step/enemy/metalgeneralmissile/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralmissile {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "PtcL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MetalGeneralMissile.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<123, 0>("step/weapon/metalgeneral/Missile", "MetalGeneralMissile", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::metalgeneralmissile
