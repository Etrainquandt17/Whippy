#include "scn/step/enemy/zankibblecutter/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace zankibblecutter {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ScaleL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Loop", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "ZankibbleCutter.AnimScript.Straight.Exec", 0, 0, 0, 0 },
    { "ZankibbleCutter.AnimScript.Circle.Exec(int)", 0, 0, 0, 0 },
    { "ZankibbleCutter.AnimScript.Circle.Exec(int)", 1, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<117, 0>("step/weapon/zankibble/Cutter", "ZankibbleCutter", 2, T_NODE_NAMES, 1, T_ANIM_ENTRIES, 10, T_SCRIPT_ENTRIES);
}

}

}}}}  // namespace scn::step::enemy::zankibblecutter
