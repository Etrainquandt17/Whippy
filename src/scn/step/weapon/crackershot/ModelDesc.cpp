#include "scn/step/weapon/crackershot/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace crackershot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<43>("step/weapon/common/CrackerBullet", "CrackerShot", 1, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("TopL");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::crackershot
