#include "scn/step/enemy/coconutbomb/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace coconutbomb {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Model",
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
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<74, 0>("step/weapon/bonkers/Coconutbomb", "CoconutBomb", 2, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::coconutbomb
