#include "scn/step/weapon/combinationdeeshot/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace combinationdeeshot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotL",
    "PtcL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<90>("step/weapon/dee/CombinationDeeShot", "CombinationDeeShot", 3, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::combinationdeeshot
