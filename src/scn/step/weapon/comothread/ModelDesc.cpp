#include "scn/step/weapon/comothread/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace comothread {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "CB1ThreadJ",
    "CB2ThreadJ",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<13>("step/weapon/como/Thread", "ComoThread", 3, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
