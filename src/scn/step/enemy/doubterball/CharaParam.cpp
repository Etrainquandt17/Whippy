#include "scn/step/enemy/doubterball/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace doubterball {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._14 = 1;
    param._47 = false;
    param._30 = 459;
    param._4b = true;
    return param;
}

enemy::CharaParam CreateFlame() {
    enemy::CharaParam param = Create();
    param._10 = 5;
    param._30 = 460;
    return param;
}

}
}
}
}
}
