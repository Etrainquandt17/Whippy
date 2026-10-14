#include "scn/step/weapon/ninjakunai/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace ninjakunai {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<38>("step/chara/hero/kirby/ninja/kunai", "NinjaKunai", 1, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::ninjakunai
