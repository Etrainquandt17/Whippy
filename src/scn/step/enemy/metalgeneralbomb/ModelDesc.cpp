#include "scn/step/enemy/metalgeneralbomb/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbomb {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Start", 0 },
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "MetalGeneralBomb.AnimScript.Wait.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralBomb.AnimScript.Blink.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<122, 0>("step/weapon/metalgeneral/Bomb", "MetalGeneralBomb", 1, T_NODE_NAMES, 2, T_ANIM_ENTRIES, 8, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::metalgeneralbomb
