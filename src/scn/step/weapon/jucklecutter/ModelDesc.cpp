#include "scn/step/weapon/jucklecutter/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace jucklecutter {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "RotL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<56>("step/weapon/juckle/Cutter", "Cutter", 3, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::jucklecutter
