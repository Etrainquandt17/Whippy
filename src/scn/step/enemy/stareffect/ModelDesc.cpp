#include "scn/step/enemy/stareffect/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace stareffect {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
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
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<100, 0>("step/chara/enemy/StarEffect", "StarEffect", 2, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::stareffect
