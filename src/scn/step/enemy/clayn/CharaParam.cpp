#include "scn/step/enemy/clayn/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace clayn {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._45 = true;
    param._47 = false;
    param._14 = 12;
    return param;
}

}
}
}
}
}
