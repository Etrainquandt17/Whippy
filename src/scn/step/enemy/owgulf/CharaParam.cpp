#include "scn/step/enemy/owgulf/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace owgulf {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 16;
    param._2c = 0.4f;
    param._10 = 19;
    return param;
}

}
}
}
}
}
