#include "scn/step/weapon/leafanpollen/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace leafanpollen {

namespace {

const char* T_NODE_NAMES[] = {
    "pSphere1",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<16>("step/weapon/leafan/Leafanseed", "LeafanSeed", 1, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
