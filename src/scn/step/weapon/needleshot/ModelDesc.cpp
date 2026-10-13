#include "scn/step/weapon/needleshot/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace needleshot {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "EffectL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<17>("step/weapon/needle/Needle", "NeedleShot", 2, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
