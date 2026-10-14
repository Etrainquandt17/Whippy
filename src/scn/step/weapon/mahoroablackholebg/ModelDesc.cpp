#include "scn/step/weapon/mahoroablackholebg/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace mahoroablackholebg {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Main", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 4, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<93>("step/weapon/mahoroabattle1/BlackWarpHoleBg", "Mahoroablackholebg", 1, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::mahoroablackholebg
