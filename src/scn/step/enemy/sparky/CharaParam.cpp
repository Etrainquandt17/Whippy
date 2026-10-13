#include "scn/step/enemy/sparky/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace sparky {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 8;
    param._14 = 12;
    param._4d = true;
    return param;
}

}
}
}
}
}
