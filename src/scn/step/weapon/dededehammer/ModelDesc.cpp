#include "scn/step/weapon/dededehammer/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace dededehammer {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "HammerHeadL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<96>("step/weapon/dedede/Hammer", "DededeHammer", 2, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
