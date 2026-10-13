#include "scn/step/weapon/EffectLocatorModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
};

}

namespace EffectLocatorModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<158>("step/weapon/common/EffectLocator", "EffectLocator", 1, T_NODE_NAMES, 0, 0, 0, 0);
}

}

}}}  // namespace scn::step::weapon
