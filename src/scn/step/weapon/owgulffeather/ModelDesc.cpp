#include "scn/step/weapon/owgulffeather/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace owgulffeather {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<53>("step/weapon/owgulf/Feather", "OwgulfFeather", 1, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::owgulffeather
