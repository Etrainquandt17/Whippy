#include "scn/step/weapon/bombbomb/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

using hel::common::FixedString;

namespace scn {
namespace step {
namespace weapon {
namespace bombbomb {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "RotL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<29>("step/chara/hero/kirby/bomb/Bomb", "BombBomb", 2, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = FixedString<40>("Model");
    return desc;
}

}

}}}}  // namespace scn::step::weapon::bombbomb
