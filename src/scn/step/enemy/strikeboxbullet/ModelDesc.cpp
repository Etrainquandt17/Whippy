#include "scn/step/enemy/strikeboxbullet/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "hel/common/FixedString.h"
#include "scn/step/enemy/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace enemy {
namespace strikeboxbullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
};


const gobj::G3DAnimDataReposDesc::Entry* T_ANIM_ENTRIES = 0;

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<140, 0>("step/weapon/common/EffectLocator", "StrikeBoxBullet", 1, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::enemy::strikeboxbullet
