#include "scn/step/enemy/glunk/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace glunk {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._c = 0.0f;
    param._14 = 8;
    param._45 = true;
    param._47 = false;
    return param;
}

}
}
}
}
}
