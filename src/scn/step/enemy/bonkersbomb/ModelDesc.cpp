#include "scn/step/enemy/bonkersbomb/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "Model",
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { "BonkersBomb.AnimScript.Wait.Exec", 0, 0, 0, 0 },
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
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<118, 0>("step/weapon/bonkers/Coconutbomb", "BonkersBomb", 2, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::bonkersbomb
