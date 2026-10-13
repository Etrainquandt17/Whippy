#include "scn/step/weapon/bowbyarrow/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace bowbyarrow {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "TailL",
    "EffectL",
    "ControlL",
    "HeadL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<55>("step/weapon/bowby/Arrow", "Arrow", 5, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

chara::ModelDesc& CreateHalcan() {
    chara::ModelDesc& desc = ModelDescUtil::CreateTmpl<146>("step/weapon/halcanbowby/Arrow", "Arrow", 5, T_NODE_NAMES, 0, 0, 0, 0);
    desc.mModel._18 = hel::common::FixedString<40>("Model");
    return desc;
}

}

}
}
}
}
