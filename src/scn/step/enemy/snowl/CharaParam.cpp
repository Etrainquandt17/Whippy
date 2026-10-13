#include "scn/step/enemy/snowl/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace snowl {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 18;
    param._14 = 8;
    return param;
}

}
}
}
}
}
