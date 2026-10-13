#include "scn/step/weapon/tsukikageshuriken/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace tsukikageshuriken {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "AnimL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "TopL", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { gobj::AnimScript::PLAY_LOOP, 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<59>("step/weapon/tsukikage/Shuriken", "Shuriken", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 1, T_SCRIPT_ENTRIES);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::tsukikageshuriken
