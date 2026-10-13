#include "scn/step/enemy/tsukikage/CharaParam.h"

#include "scn/step/enemy/common/ParamBase.h"

namespace scn {
namespace step {
namespace enemy {
namespace tsukikage {
namespace CharaParam {

enemy::CharaParam Create() {
    enemy::CharaParam param = common::ParamBase::Create();
    param._10 = 20;
    param._14 = 12;
    param._48 = false;
    return param;
}

}
}
}
}
}
