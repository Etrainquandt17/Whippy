#include "scn/step/weapon/hammerhammer/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace hammerhammer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "AllL",
    "HammerheadJ",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<32>("step/chara/hero/kirby/hammer/Hammer", "HammerHammer", 3, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::hammerhammer
