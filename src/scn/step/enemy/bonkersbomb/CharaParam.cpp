#include "scn/step/enemy/bonkersbomb/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace bonkersbomb {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._47 = false;
    param._2c = 0.35f;
    param._46 = false;
    return param;
}

}
}
}
}
}
