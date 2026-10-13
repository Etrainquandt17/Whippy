#include "scn/step/enemy/doubterbomb/ModelDesc.h"

#include "gobj/AnimScript.h"
#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubterbomb {

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
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<112, 0>("step/chara/enemy/DoubterBomb", "DoubterBomb", 1, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<112, 0>("step/chara/enemy/DoubterBombEx", "DoubterBomb", 1, T_NODE_NAMES, 0, T_ANIM_ENTRIES, 7, T_SCRIPT_ENTRIES);
    return desc;
}

}

}}}}  // namespace scn::step::enemy::doubterbomb
