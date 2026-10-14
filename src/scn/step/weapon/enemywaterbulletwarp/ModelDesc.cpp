#include "scn/step/weapon/enemywaterbulletwarp/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace enemywaterbulletwarp {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL", "Control1J", "Control2J", "Control3J", "WnWaterWarpM",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Loop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc =
        ModelDescUtil::CreateTmpl<46>("step/weapon/wgalbo/WaterWarp", "EnemyWaterBulletWarp", 5, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::enemywaterbulletwarp
