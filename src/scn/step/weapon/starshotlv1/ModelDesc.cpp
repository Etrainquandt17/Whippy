#include "scn/step/weapon/starshotlv1/ModelDesc.h"

#include "scn/step/weapon/ModelDescUtil.h"

namespace scn {
namespace step {
namespace weapon {
namespace starshotlv1 {

namespace {

const char* T_NODE_NAMES[] = {
    "TopL",
    "ControlL",
    "PtclL",
};

}

namespace ModelDesc {

chara::ModelDesc& Create() {
    return ModelDescUtil::CreateTmpl<0>("step/weapon/normal/Star", "StarShotLv1", 3, T_NODE_NAMES, 0, 0, 0, 0);
}

}

}
}
}
}
