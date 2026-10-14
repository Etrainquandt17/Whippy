#include "scn/step/enemy/metalgeneralbit/ModelDesc.h"

#include "scn/step/enemy/ModelDescUtil.h"

namespace scn {
namespace step {
namespace enemy {
namespace metalgeneralbit {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "AllL",
};

const gobj::G3DAnimDataReposDesc::Entry T_ANIM_ENTRIES[] = {
    { "Wait1", 0 },
    { "Wait2", 0 },
    { "Shoot", 0 },
    { "BeamStart", 0 },
    { "Beam", 0 },
    { "BeamWait", 0 },
    { "BeamEnd", 0 },
};

const gobj::ScriptDesc::Entry T_SCRIPT_ENTRIES[] = {
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralBit.AnimScript.Fly.Exec", 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0 },
    { "MetalGeneralBit.AnimScript.Appear.Exec", 0, 0, 0, 0 },
    { "MetalGeneralBit.AnimScript.Shot.Exec", 0, 0, 0, 0 },
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<120, 0>("step/chara/enemy/metalbit/Model", "MetalGeneralBall", 2, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/metalbit/Motion";
    return desc;
}

chara::ModelDesc& CreateEx() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<121, 0>("step/chara/enemy/metalbit/ModelEx", "MetalGeneralBit", 2, T_NODE_NAMES, 7, T_ANIM_ENTRIES, 9, T_SCRIPT_ENTRIES);
    desc._8 = "step/chara/enemy/metalbit/Motion";
    return desc;
}

}

}}}}  // namespace scn::step::enemy::metalgeneralbit
