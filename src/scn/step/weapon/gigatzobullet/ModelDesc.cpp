#include "scn/step/weapon/gigatzobullet/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace gigatzobullet {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TransL",
    "ControlL",
    "RotL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<49>("step/weapon/gigatzo/Bomb", "GigatzoBullet", 4, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

chara::ModelDesc& CreateVolt() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<60>("step/weapon/volttzo/Bomb", "VolttzoBullet", 4, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

chara::ModelDesc& CreateCold() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<76>("step/weapon/coldtzo/Bomb", "ColdtzoBullet", 4, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::gigatzobullet
