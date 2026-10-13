#include "scn/step/enemy/searches/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace searches {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._c = 0.0f;
    param._10 = 22;
    return param;
}

}
}
}
}
}
