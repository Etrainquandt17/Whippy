#include "scn/step/enemy/pierce/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace pierce {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 16;
    param._14 = 8;
    return param;
}

}
}
}
}
}
